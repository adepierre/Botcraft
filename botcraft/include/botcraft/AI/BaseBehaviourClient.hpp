#pragma once

#include <iostream>

#include "botcraft/AI/BehaviourClient.hpp"
#include "botcraft/AI/BehaviourTree.hpp"
#include "botcraft/Network/NetworkManager.hpp"

namespace Botcraft
{
    namespace AI
    {
        /// <summary>
        /// The base class you should inherit if you need to
        /// add some specific Handle functions for packets AND
        /// want to use behaviour tree AI system.
        /// Derived class are defined this way:
        /// class MyClass : public BaseBehaviourClient<MyClass>
        /// </summary>
        /// <typeparam name="TDerived">Any class inheriting from BaseBehaviourClient</typeparam>
        template<typename TDerived>
        class BaseBehaviourClient : public BehaviourClient
        {
            // Custom internal class exceptions used 
            // to interrupt behaviours processing
        private:
            class SwapTreeException : public std::exception
            {
            };
            class InterruptedException : public std::exception
            {
            };

        public:
            BaseBehaviourClient(const bool use_renderer_, const bool afk_only_ = false) :
                BehaviourClient(use_renderer_, afk_only_)
            {
                swap_tree = false;
            }

            virtual ~BaseBehaviourClient()
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

            /// <summary>
            /// Save the given tree to replace the current one as soon as possible.
            /// </summary>
            /// <param name="tree_">The new tree</param>
            void SetBehaviourTree(const std::shared_ptr<BehaviourTree<TDerived> >& tree_)
            {
                std::lock_guard<std::mutex> behaviour_guard(behaviour_mutex);
                swap_tree = true;
                new_tree = tree_;
            }

            /// <summary>
            /// Can be called to pause the execution of the internal
            /// tree function. Call it in long function so the behaviour
            /// can be interrupted.
            /// </summary>
            virtual void Yield() override
            {
                std::unique_lock<std::mutex> lock(behaviour_mutex);
                behaviour_cond_var.notify_all();
                behaviour_cond_var.wait(lock);
                if (should_be_closed)
                {
                    throw InterruptedException();
                }
                else if (swap_tree)
                {
                    throw SwapTreeException();
                }
            }

            /// <summary>
            /// Start the behaviour thread loop.
            /// </summary>
            void StartBehaviour()
            {
                std::unique_lock<std::mutex> lock(behaviour_mutex);
                behaviour_thread = std::thread(&BaseBehaviourClient<TDerived>::TreeLoop, this);
                // Wait for the first Yield call to be sure 
                // the thread is started and ready to run
                behaviour_cond_var.wait(lock);
            }

            /// <summary>
            /// Blocking call, will return only when the client is
            /// disconnected from the server.
            /// </summary>
            void RunBehaviourUntilClosed()
            {
                if (!behaviour_thread.joinable())
                {
                    StartBehaviour();
                }

                // Main behaviour loop
                while (!should_be_closed)
                {
                    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
                    std::chrono::system_clock::time_point end = start + std::chrono::milliseconds(10);

                    BehaviourStep();

                    std::this_thread::sleep_until(end);
                }
            }

            /// <summary>
            /// Perform one step of the behaviour tree.
            /// Don't forget to call StartBehaviour before.
            /// </summary>
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

        private:
            void TreeLoop()
            {
                while (true)
                {
                    try
                    {
                        if (tree)
                        {
                            tree->Tick(static_cast<TDerived&>(*this));
                        }
                        Yield();
                    }
                    // We need to update the tree with the new one
                    catch (const SwapTreeException&)
                    {
                        tree = new_tree;
                        new_tree = nullptr;
                        swap_tree = false;
                        blackboard.Clear();
                        continue;
                    }
                    // We need to stop the behaviour thread
                    catch (const InterruptedException&)
                    {
                        return;
                    }
                    catch (std::exception& e)
                    {
                        std::cerr << "Exception caught during tree ticking: " << e.what() << ". Stopping behaviour." << std::endl;
                        return;
                    }
                    catch (...)
                    {
                        std::cerr << "Unknown exception caught during tree ticking. Stopping behaviour." << std::endl;
                        return;
                    }
                }
            }

        private:
            std::shared_ptr<BehaviourTree<TDerived> > tree;
            std::shared_ptr<BehaviourTree<TDerived> > new_tree;
            bool swap_tree;

            std::thread behaviour_thread;
            std::condition_variable behaviour_cond_var;
            std::mutex behaviour_mutex;
        };
    } // namespace AI
} // namespace Botcraft
