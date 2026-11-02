#pragma once

#include <atomic>
#include <functional>
#include <type_traits>
#include <utility>

#include "botcraft/AI/BehaviourClient.hpp"
#include "botcraft/AI/BehaviourTree.hpp"
#include "botcraft/Network/NetworkManager.hpp"
#include "botcraft/Utilities/Logger.hpp"
#include "botcraft/Utilities/SleepUtilities.hpp"
#if USE_GUI
#include "botcraft/Renderer/RenderingManager.hpp"
#endif

namespace Botcraft
{
    /// @brief The base class you should inherit if you need to
    /// implement some custom Handle functions AND need to add
    /// custom fields to your derived class. If you just need
    /// some custom Handle, inheriting SimpleBehaviourClient is
    /// sufficient.
    /// @tparam TDerived Any class inheriting this class (see SimpleBehaviourClient)
    template<typename TDerived>
    class TemplatedBehaviourClient : public BehaviourClient
    {
    private:
        /// @brief Custom internal type used when the tree needs
        /// to be changed. It does not inherit std::exception to
        /// prevent tree components from catching it
        class SwapTree
        {
        };
        /// @brief Custom internal type used when the tree needs
        /// to be stopped. It does not inherit std::exception to
        /// prevent tree components from catching it
        class Interrupted
        {
        };

    public:
        TemplatedBehaviourClient() : BehaviourClient()
        {
            swap_tree = false;
        }

        virtual ~TemplatedBehaviourClient()
        {
            // Make sure should_be_closed is set to false
            // otherwise the behaviour_thread will not exit
            // properly
            {
                std::lock_guard<std::mutex> behaviour_guard(behaviour_mutex);
                should_be_closed = true;
            }

            behaviour_cond_var.notify_all();
            if (behaviour_thread.joinable())
            {
                behaviour_thread.join();
            }
        }

        /// @brief Save the given tree to replace the current one as soon as possible.
        /// @param tree_ The new tree
        /// @param blackboard_ Initial values to put into the blackboard when swapping tree
        void SetBehaviourTree(const std::shared_ptr<BehaviourTree<TDerived> >& tree_, const std::map<std::string, std::any>& blackboard_ = {})
        {
            std::lock_guard<std::mutex> behaviour_guard(behaviour_mutex);
            swap_tree = true;
            new_tree = tree_;
            new_blackboard = blackboard_;
        }

        /// @brief Can be called to pause the execution of the internal
        /// tree function. Call it in long function so the behaviour
        /// can be interrupted.
        virtual void Yield() override
        {
            std::unique_lock<std::mutex> lock(behaviour_mutex);
            behaviour_cond_var.notify_all();
            behaviour_cond_var.wait(lock);
            if (should_be_closed)
            {
                throw Interrupted();
            }
            else if (swap_tree)
            {
                throw SwapTree();
            }
        }

        /// @brief Start the behaviour thread loop.
        void StartBehaviour()
        {
            tree_loop_ready = false;
            behaviour_thread = std::thread(&TemplatedBehaviourClient<TDerived>::TreeLoop, this);

            // Wait for the thread to start and ready to run
            while (!tree_loop_ready)
            {
                Utilities::SleepFor(std::chrono::milliseconds(10));
            }
        }

        /// @brief Blocking call, will return only when the client is
        /// disconnected from the server.
        void RunBehaviourUntilClosed()
        {
            if (!behaviour_thread.joinable())
            {
                StartBehaviour();
            }

            // Main behaviour loop
            while (!should_be_closed)
            {
                std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
                std::chrono::steady_clock::time_point end = start + std::chrono::milliseconds(10);

                BehaviourStep();

                Utilities::SleepUntil(end);
            }
        }

        /// @brief Perform one step of the behaviour tree.
        /// Don't forget to call StartBehaviour before.
        void BehaviourStep()
        {
            if (should_be_closed || !network_manager || network_manager->GetConnectionState() != ProtocolCraft::ConnectionState::Play)
            {
                return;
            }

            std::unique_lock<std::mutex> lock(behaviour_mutex);
            // Resume tree ticking
            behaviour_cond_var.notify_all();
            // Wait for the next call to Yield()
            behaviour_cond_var.wait(lock);
        }

        /// @brief Set a tree to execute the given action once and block until done.
        /// This will change the current tree. BehaviourStep should **NOT** be called
        /// by another thread simultaneously. It means you should **NOT** call
        /// RunBehaviourUntilClosed when using this sync version.
        /// @param timeout_ms Max running time of the function in ms, ignored if 0
        /// @param ...args Parameters passed to create tree leaf
        /// @return Return value of the action (success/failure)
        template<typename... Args>
        Status SyncAction(const int timeout_ms, Args&&... args)
        {
            // Make sure the behaviour thread is running
            if (!behaviour_thread.joinable())
            {
                StartBehaviour();
            }

            // Shared pointers so they still exist for the tree even if we exit this function
            std::shared_ptr<Status> return_value = std::make_shared<Status>(Status::Failure);
            std::shared_ptr<std::atomic<bool>> done = std::make_shared<std::atomic<bool>>(false);

            // Wrap the action with a try catch so a throw becomes a failure instead of a deadlocked thread waiting for an update that will never come
            const std::pair<std::string, std::function<Status(TDerived&)>> wrapped = MakeSyncActionLeaf<TDerived>(std::forward<Args>(args)...);

            SetBehaviourTree(Builder<TDerived>()
                .sequence()
                    .succeeder().sequence()
                        .leaf(wrapped.first, wrapped.second)
                        .leaf([return_value](TDerived&) { *return_value = Status::Success; return Status::Success; })
                    .end()
                    .leaf([done](TDerived& c) { c.SetBehaviourTree(nullptr); *done = true; return Status::Success; })
                .end()
            );

            // Run until the last leaf set done
            const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            while (!*done)
            {
                // Timeout, reset tree and return
                if (should_be_closed || (timeout_ms > 0 && std::chrono::steady_clock::now() - start > std::chrono::milliseconds(timeout_ms)))
                {
                    LOG_WARNING("Timeout during SyncAction");
                    SetBehaviourTree(nullptr);
                    BehaviourStep();
                    return Status::Failure;
                }

                const std::chrono::steady_clock::time_point iter_end = std::chrono::steady_clock::now() + std::chrono::milliseconds(10);
                BehaviourStep();
                Utilities::SleepUntil(iter_end);
            }

            return *return_value;
        }


        /// @brief Set a tree to execute the given action once and block until done.
        /// This will change the current tree. BehaviourStep should **NOT** be called
        /// by another thread simultaneously. It means you should **NOT** call
        /// RunBehaviourUntilClosed when using this sync version. This version has no
        /// timeout and will run until the tree ends.
        /// @param ...args Parameters passed to create tree leaf
        template<typename... Args>
        Status SyncAction(Args&&... args)
        {
            return SyncAction(0, std::forward<Args>(args)...);
        }

        void OnTreeChanged(const BaseNode* root)
        {
            const std::string& tree_name = root != nullptr ? root->GetName() : "nullptr";
            LOG_INFO("Behaviour tree changed" << (tree_name.empty() ? " (anonymous tree)" : (" to " + tree_name)));
#if USE_GUI
            if (rendering_manager != nullptr)
            {
                rendering_manager->SetCurrentBehaviourTree(root);
            }
#endif
        }

#if USE_GUI
        void OnFullTreeStart()
        {
            if (rendering_manager != nullptr)
            {
                rendering_manager->ResetBehaviourState();
            }
        }

        void OnNodeStartTick()
        {
            if (rendering_manager != nullptr)
            {
                rendering_manager->BehaviourStartTick();
                while (rendering_manager->IsBehaviourGUIPaused())
                {
                    Yield();
                }
            }
        }

        void OnNodeEndTick(const Status s)
        {
            if (rendering_manager != nullptr)
            {
                rendering_manager->BehaviourEndTick(s == Status::Success);
            }
        }

        void OnNodeTickChild(const size_t i)
        {
            if (rendering_manager != nullptr)
            {
                rendering_manager->BehaviourTickChild(i);
            }
        }
#endif

    private:
        /// @brief Wrap a SyncAction action so a throw is reported as a failure
        /// instead of stopping the behaviour thread.
        template<typename Context, typename F, typename... Params>
        static std::function<Status(Context&)> WrapSyncAction(F&& f, Params&&... params)
        {
            return [f = std::forward<F>(f), params...](Context& c) mutable {
                try
                {
                    return f(c, params...);
                }
                catch (const std::exception& ex)
                {
                    LOG_ERROR("Exception in SyncAction:\n" << ex.what());
                    return Status::Failure;
                }
            };
        }

        template<typename Context, typename F, typename... Params, typename = std::enable_if_t<!std::is_convertible_v<F, std::string>>>
        static std::pair<std::string, std::function<Status(Context&)>> MakeSyncActionLeaf(F&& f, Params&&... params)
        {
            return { std::string(), WrapSyncAction<Context>(std::forward<F>(f), std::forward<Params>(params)...) };
        }

        template<typename Context, typename S, typename F, typename... Params, typename = std::enable_if_t<std::is_convertible_v<S, std::string>>>
        static std::pair<std::string, std::function<Status(Context&)>> MakeSyncActionLeaf(S&& s, F&& f, Params&&... params)
        {
            return { std::string(s), WrapSyncAction<Context>(std::forward<F>(f), std::forward<Params>(params)...) };
        }

        void TreeLoop()
        {
            Logger::GetInstance().RegisterThread("Behaviour - " + GetNetworkManager()->GetMyName());
            tree_loop_ready = true;
            while (true)
            {
                try
                {
                    if (tree)
                    {
#if USE_GUI
                        OnFullTreeStart();
#endif
                        tree->Tick(static_cast<TDerived&>(*this));
                    }
                    Yield();
                }
                // We need to update the tree with the new one
                catch (const SwapTree&)
                {
                    {
                        std::lock_guard<std::mutex> behaviour_guard(behaviour_mutex);
                        tree = new_tree;
                        new_tree = nullptr;
                        swap_tree = false;
                        OnTreeChanged(tree.get());
                        blackboard.Reset(new_blackboard);
                    }
                    continue;
                }
                // We need to stop the behaviour thread
                catch (const Interrupted&)
                {
                    return;
                }
                catch (const std::exception& e)
                {
                    LOG_ERROR("Exception caught during tree ticking:\n" << e.what() << "\nStopping behaviour.");
                    return;
                }
                catch (...)
                {
                    LOG_ERROR("Unknown exception caught during tree ticking. Stopping behaviour.");
                    return;
                }
            }
        }

    private:
        std::shared_ptr<BehaviourTree<TDerived> > tree;
        std::shared_ptr<BehaviourTree<TDerived> > new_tree;
        std::map<std::string, std::any> new_blackboard;
        bool swap_tree;

        std::thread behaviour_thread;
        std::condition_variable behaviour_cond_var;
        std::mutex behaviour_mutex;

        std::atomic<bool> tree_loop_ready;
    };
} // namespace Botcraft
