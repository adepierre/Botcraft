#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <string>
#include <stdexcept>

#include "botcraft/AI/BaseNode.hpp"
#include "botcraft/AI/Status.hpp"
#include "botcraft/Utilities/Templates.hpp"

// A behaviour tree implementation following this blog article
// https://www.gamasutra.com/blogs/ChrisSimpson/20140717/221339/Behavior_trees_for_AI_How_they_work.php

// First version of this code was inspired by
// https://github.com/arvidsson/BrainTree

namespace Botcraft
{
    // Define some templates functions used as update
    // notifications during node ticking
    GENERATE_CHECK_HAS_FUNC(OnNodeStartTick);
    GENERATE_CHECK_HAS_FUNC(OnNodeEndTick);
    GENERATE_CHECK_HAS_FUNC(OnNodeTickChild);

    template<typename Context>
    class Node : public BaseNode
    {
        using BaseNode::BaseNode;
    public:
        virtual ~Node() {}
        Status Tick(Context& context) const
        {
            if constexpr (has_OnNodeStartTick<Context, void()>)
            {
                context.OnNodeStartTick();
            }

            const Status result = this->TickImpl(context);

            if constexpr (has_OnNodeEndTick<Context, void(Status)>)
            {
                context.OnNodeEndTick(result);
            }

            return result;
        }

    protected:
        virtual Status TickImpl(Context& context) const = 0;
    };


    template<typename Context>
    class Composite : public Node<Context>
    {
        using Node<Context>::Node;
    public:
        virtual ~Composite() {}

        void AddChild(const std::shared_ptr<Node<Context>>& child)
        {
            children.push_back(child);
        }

        virtual BehaviourNodeType GetNodeType() const override
        {
            return BehaviourNodeType::Composite;
        }
        
        virtual size_t GetNumChildren() const override
        {
            return children.size();
        }

        virtual const BaseNode* GetChild(const size_t index) const override
        {
            return children[index].get();
        }

    protected:
        Status TickChild(Context& context, const size_t index) const
        {
            if (index >= children.size())
            {
                throw std::runtime_error(std::string("Out of bounds child ticking in ") + this->GetFullDescriptor() + " at index " + std::to_string(index));
            }

            if (children[index] == nullptr)
            {
                throw std::runtime_error(std::string("Nullptr child in ") + this->GetFullDescriptor() + " at index " + std::to_string(index));
            }

            if constexpr (has_OnNodeTickChild<Context, void(size_t)>)
            {
                context.OnNodeTickChild(index);
            }

            try
            {
                return children[index]->Tick(context);
            }
            catch (const std::exception& ex)
            {
                throw std::runtime_error(std::string("In ") + this->GetFullDescriptor() + " while Ticking child " + std::to_string(index) + "\n" +
                    ex.what());
            }
        }

    private:
        std::vector<std::shared_ptr<Node<Context>>> children;
    };

    template<typename Context>
    class Decorator : public Node<Context>
    {
        using Node<Context>::Node;
    public:
        virtual ~Decorator() {}

        void SetChild(std::shared_ptr<Node<Context>> child_)
        {
            child = child_;
        }

        virtual BehaviourNodeType GetNodeType() const override
        {
            return BehaviourNodeType::Decorator;
        }

        virtual size_t GetNumChildren() const override
        {
            return child == nullptr ? 0 : 1;
        }

        virtual const BaseNode* GetChild(const size_t index) const override
        {
            return child.get();
        }

    protected:
        Status TickChild(Context& context) const
        {
            if (child == nullptr)
            {
                throw std::runtime_error("Nullptr child in decorator " + this->GetFullDescriptor());
            }

            if constexpr (has_OnNodeTickChild<Context, void(size_t)>)
            {
                context.OnNodeTickChild(0);
            }

            try
            {
                return child->Tick(context);
            }
            catch (const std::exception& ex)
            {
                throw std::runtime_error(std::string("In ") + this->GetFullDescriptor() + "\n" +
                    ex.what());
            }
        }

    private:
        std::shared_ptr<Node<Context>> child;
    };

    template<typename Context>
    class Leaf final : public Node<Context>
    {
    public:
        Leaf() = delete;

        template<typename FuncType>
        Leaf(const std::string& s, FuncType func_) : Node<Context>(s), func(func_) {}

        template<typename FuncType, typename... Args>
        Leaf(const std::string& s, FuncType func_, Args&&... args) : Node<Context>(s)
        {
            func = [=](Context& c) -> Status { return func_(c, (args)...); };
        }

        virtual ~Leaf() {}

        virtual BehaviourNodeType GetNodeType() const override
        {
            return BehaviourNodeType::Leaf;
        }

        virtual size_t GetNumChildren() const override
        {
            return 0;
        }

        virtual const BaseNode* GetChild(const size_t index) const override
        {
            return nullptr;
        }

    protected:
        virtual Status TickImpl(Context& context) const override
        {
            try
            {
                return func(context);
            }
            catch (const std::exception& ex)
            {
                if (this->name.empty())
                {
                    throw;
                }
                throw std::runtime_error(std::string("In leaf \"") + this->name + "\"\n" +
                    ex.what());
            }
        }

    private:
        std::function<Status(Context&)> func;
    };

    template<typename Context>
    class BehaviourTree final : public Node<Context>
    {
        using Node<Context>::Node;
    public:
        virtual ~BehaviourTree() {}

        void SetRoot(const std::shared_ptr<Node<Context>> node) { root = node; }

        virtual BehaviourNodeType GetNodeType() const override
        {
            return BehaviourNodeType::Tree;
        }

        virtual size_t GetNumChildren() const override
        {
            return root == nullptr ? 0 : 1;
        }

        virtual const BaseNode* GetChild(const size_t index) const override
        {
            return root.get();
        }

    protected:
        virtual Status TickImpl(Context& context) const override
        {
            if (root == nullptr)
            {
                throw std::runtime_error(std::string("Nullptr tree when trying to tick tree ") + this->GetFullDescriptor());
            }

            if constexpr (has_OnNodeTickChild<Context, void(size_t)>)
            {
                context.OnNodeTickChild(0);
            }

            try
            {
                return root->Tick(context);
            }
            catch (const std::exception& ex)
            {
                if (this->name.empty())
                {
                    throw;
                }
                throw std::runtime_error(std::string("In tree \"") + this->name + "\"\n" +
                    ex.what());
            }
        }

    private:
        std::shared_ptr<Node<Context>> root;
    };

    /// @brief Sequence implementation. Run all children until
    /// one fails. Succeeds if all children succeed.
    /// Equivalent to a logical AND.
    /// @tparam Context The tree context type
    template<typename Context>
    class Sequence final : public Composite<Context>
    {
        using Composite<Context>::Composite;
    protected:
        virtual Status TickImpl(Context& context) const override
        {
            for (size_t i = 0; i < this->GetNumChildren(); ++i)
            {
                if (this->TickChild(context, i) == Status::Failure)
                {
                    return Status::Failure;
                }
            }
            // If we are here, all children succeeded
            return Status::Success;
        }
    };

    /// @brief Selector implementation. Run all children until
    /// one succeeds. Fails if all children fail.
    /// Equivalent to a logical OR.
    /// @tparam Context The tree context type
    template<typename Context>
    class Selector final : public Composite<Context>
    {
        using Composite<Context>::Composite;
    protected:
        virtual Status TickImpl(Context& context) const override
        {
            for (size_t i = 0; i < this->GetNumChildren(); ++i)
            {
                if (this->TickChild(context, i) == Status::Success)
                {
                    return Status::Success;
                }
            }

            // If we are here, all children failed
            return Status::Failure;
        }
    };



    // Common Decorators implementations
        
    /// @brief A Decorator that inverts the result of its child.
    /// @tparam Context The tree context type
    template<typename Context>
    class Inverter final : public Decorator<Context>
    {
        using Decorator<Context>::Decorator;
    protected:
        virtual Status TickImpl(Context& context) const override
        {
            return this->TickChild(context) == Status::Failure ? Status::Success : Status::Failure;
        }
    };

    /// @brief A Decorator that always return success,
    /// independently of the result of its child.
    /// Can be combined with an inverter for Failure.
    /// @tparam Context The tree context type
    template<typename Context>
    class Succeeder final : public Decorator<Context>
    {
        using Decorator<Context>::Decorator;
    protected:
        virtual Status TickImpl(Context& context) const override
        {
            this->TickChild(context);
            return Status::Success;
        }
    };

    /// @brief A Decorator that ticks its child n times
    /// (repeat until first success if n == 0).
    /// Always returns success.
    /// @tparam Context The tree context type
    template<typename Context>
    class Repeater final : public Decorator<Context>
    {
    public:
        Repeater(const std::string& s, const size_t n_) : Decorator<Context>(s), n(n_) {}

    protected:
        virtual Status TickImpl(Context& context) const override
        {
            Status child_status = Status::Failure;
            size_t counter = 0;
            while ((child_status == Status::Failure && n == 0) || counter < n)
            {
                child_status = this->TickChild(context);
                counter += 1;
            }
            return Status::Success;
        }

    private:
        size_t n;
    };




    // Builder implementation for easy tree building

    template<typename Parent, typename Context>
    class DecoratorBuilder;

    template<typename Context>
    class Builder;

    template<typename Parent, typename Context>
    class CompositeBuilder
    {
    public:
        CompositeBuilder(Parent* parent, Composite<Context>* node) : parent(parent), node(node) {}

        /// @brief To add a named leaf
        /// @tparam S std::string convertible type
        /// @tparam ...Args leaf function and params
        /// @tparam Do not use this template if first param is not a string
        /// @param s Leaf name
        /// @param ...args leaf function and params
        /// @return A composite builder to continue building the tree
        template<
            typename S,
            typename... Args,
            typename = typename std::enable_if_t<std::is_convertible_v<S, std::string>>
        >
        CompositeBuilder leaf(const S& s, Args&&... args)
        {
            auto child = std::make_shared<Leaf<Context> >(s, std::forward<Args>(args)...);
            node->AddChild(child);
            return *this;
        }

        /// @brief To add an anonymous leaf
        /// @tparam ...Args 
        /// @param ...args 
        /// @return 
        template<typename... Args>
        CompositeBuilder leaf(Args&&... args)
        {
            auto child = std::make_shared<Leaf<Context> >("", std::forward<Args>(args)...);
            node->AddChild(child);
            return *this;
        }

        // To add a tree
        CompositeBuilder tree(std::shared_ptr<BehaviourTree<Context> > arg)
        {
            node->AddChild(arg);
            return *this;
        }


        // Composite
        // Custom function to add a sequence
        CompositeBuilder<CompositeBuilder, Context> sequence(const std::string& s = "")
        {
            auto child = std::make_shared<Sequence<Context>>(s);
            node->AddChild(child);
            return CompositeBuilder<CompositeBuilder, Context>(this, (Sequence<Context>*)child.get());
        }

        // Custom function to add a selector
        CompositeBuilder<CompositeBuilder, Context> selector(const std::string& s = "")
        {
            auto child = std::make_shared<Selector<Context>>(s);
            node->AddChild(child);
            return CompositeBuilder<CompositeBuilder, Context>(this, (Selector<Context>*)child.get());
        }

        // To add any other type of composite
        template<
            typename CompositeType,
            typename... Args,
            typename S,
            typename = typename std::enable_if_t<std::is_convertible_v<S, std::string>>
        >
        CompositeBuilder<CompositeBuilder, Context> composite(const S& s, Args&&... args)
        {
            auto child = std::make_shared<CompositeType>(s, std::forward<Args>(args)...);
            node->AddChild(child);
            return CompositeBuilder<CompositeBuilder, Context>(this, (CompositeType*)child.get());
        }

        template<
            typename CompositeType,
            typename... Args
        >
        CompositeBuilder<CompositeBuilder, Context> composite(Args&&... args)
        {
            auto child = std::make_shared<CompositeType>("", std::forward<Args>(args)...);
            node->AddChild(child);
            return CompositeBuilder<CompositeBuilder, Context>(this, (CompositeType*)child.get());
        }

        // Decorator
        // Inverter
        DecoratorBuilder<CompositeBuilder, Context> inverter(const std::string& s = "")
        {
            auto child = std::make_shared<Inverter<Context>>(s);
            node->AddChild(child);
            return DecoratorBuilder<CompositeBuilder, Context>(this, (Inverter<Context>*)child.get());
        }

        // Succeeder
        DecoratorBuilder<CompositeBuilder, Context> succeeder(const std::string& s = "")
        {
            auto child = std::make_shared<Succeeder<Context>>(s);
            node->AddChild(child);
            return DecoratorBuilder<CompositeBuilder, Context>(this, (Succeeder<Context>*)child.get());
        }

        // Repeater
        DecoratorBuilder<CompositeBuilder, Context> repeater(const size_t n)
        {
            auto child = std::make_shared<Repeater<Context>>("", n);
            node->AddChild(child);
            return DecoratorBuilder<CompositeBuilder, Context>(this, (Repeater<Context>*)child.get());
        }

        // Repeater
        DecoratorBuilder<CompositeBuilder, Context> repeater(const std::string& s, const size_t n)
        {
            auto child = std::make_shared<Repeater<Context>>(s, n);
            node->AddChild(child);
            return DecoratorBuilder<CompositeBuilder, Context>(this, (Repeater<Context>*)child.get());
        }

        // To add any other type of decorator
        template<
            typename DecoratorType,
            typename... Args,
            typename S,
            typename = typename std::enable_if_t<std::is_convertible_v<S, std::string>>
        >
        DecoratorBuilder<CompositeBuilder, Context> decorator(const S& s, Args&&... args)
        {
            auto child = std::make_shared<DecoratorType>(s, std::forward<Args>(args)...);
            node->AddChild(child);
            return DecoratorBuilder<CompositeBuilder, Context>(this, (DecoratorType*)child.get());
        }
        template<
            typename DecoratorType,
            typename... Args
        >
        DecoratorBuilder<CompositeBuilder, Context> decorator(Args&&... args)
        {
            auto child = std::make_shared<DecoratorType>("", std::forward<Args>(args)...);
            node->AddChild(child);
            return DecoratorBuilder<CompositeBuilder, Context>(this, (DecoratorType*)child.get());
        }

        std::conditional_t<
            std::is_same_v<Parent, Builder<Context>>, // If the parent is a Builder
            std::shared_ptr<BehaviourTree<Context>>,  // Then return the tree as we can't add anything else after the root
            Parent&                                   // Else return the parent to continue the chain
        > end()
        {
            if constexpr (std::is_same_v<Parent, Builder<Context>>)
            {
                return parent->build();
            }
            else
            {
                return *parent;
            }
        }

    private:
        Parent* parent;
        Composite<Context>* node;
    };

    template<typename Parent, typename Context>
    class DecoratorBuilder
    {
    public:
        DecoratorBuilder(Parent* parent, Decorator<Context>* node) : parent(parent), node(node) {}

        // To add a leaf
        template<
            typename S,
            typename... Args,
            typename = typename std::enable_if_t<std::is_convertible_v<S, std::string>>
        >
        std::conditional_t<
            std::is_same_v<Parent, Builder<Context>>, // If the parent is a Builder
            std::shared_ptr<BehaviourTree<Context>>,  // Then return the tree as we can't add anything else after the root
            Parent&                                   // Else return the parent to continue the chain
        > leaf(const S& s, Args&&... args)
        {
            auto child = std::make_shared<Leaf<Context> >(s, std::forward<Args>(args)...);
            node->SetChild(child);
            if constexpr (std::is_same_v<Parent, Builder<Context>>)
            {
                return parent->build();
            }
            else
            {
                return *parent;
            }
        }
        template<typename... Args>
        std::conditional_t<
            std::is_same_v<Parent, Builder<Context>>, // If the parent is a Builder
            std::shared_ptr<BehaviourTree<Context>>,  // Then return the tree as we can't add anything else after the root
            Parent&                                   // Else return the parent to continue the chain
        > leaf(Args&&... args)
        {
            auto child = std::make_shared<Leaf<Context> >("", std::forward<Args>(args)...);
            node->SetChild(child);
            if constexpr (std::is_same_v<Parent, Builder<Context>>)
            {
                return parent->build();
            }
            else
            {
                return *parent;
            }
        }

        // To add a tree
        std::conditional_t<
            std::is_same_v<Parent, Builder<Context>>, // If the parent is a Builder
            std::shared_ptr<BehaviourTree<Context>>,  // Then return the tree as we can't add anything else after the root
            Parent&                                   // Else return the parent to continue the chain
        > tree(std::shared_ptr<BehaviourTree<Context> > arg)
        {
            node->SetChild(arg);
            if constexpr (std::is_same_v<Parent, Builder<Context>>)
            {
                return parent->build();
            }
            else
            {
                return *parent;
            }
        }


        // Composites
        // Custom function to add a sequence
        CompositeBuilder<Parent, Context> sequence(const std::string& s = "")
        {
            auto child = std::make_shared<Sequence<Context>>(s);
            node->SetChild(child);
            return CompositeBuilder<Parent, Context>(parent, (Sequence<Context>*)child.get());
        }

        // Custom function to add a selector
        CompositeBuilder<Parent, Context> selector(const std::string& s = "")
        {
            auto child = std::make_shared<Selector<Context>>(s);
            node->SetChild(child);
            return CompositeBuilder<Parent, Context>(parent, (Selector<Context>*)child.get());
        }

        // To add any other type of composite
        template<
            typename CompositeType,
            typename... Args,
            typename S,
            typename = typename std::enable_if_t<std::is_convertible_v<S, std::string>>
        >
        CompositeBuilder<Parent, Context> composite(const S& s, Args&&... args)
        {
            auto child = std::make_shared<CompositeType>(s, std::forward<Args>(args)...);
            node->SetChild(child);
            return CompositeBuilder<Parent, Context>(parent, (CompositeType*)child.get());
        }
        template<
            typename CompositeType,
            typename... Args
        >
        CompositeBuilder<Parent, Context> composite(Args&&... args)
        {
            auto child = std::make_shared<CompositeType>("", std::forward<Args>(args)...);
            node->SetChild(child);
            return CompositeBuilder<Parent, Context>(parent, (CompositeType*)child.get());
        }

        // Decorator
        // Inverter
        DecoratorBuilder<Parent, Context> inverter(const std::string& s = "")
        {
            auto child = std::make_shared<Inverter<Context>>(s);
            node->SetChild(child);
            return DecoratorBuilder<Parent, Context>(parent, (Inverter<Context>*)child.get());
        }

        // Succeeder
        DecoratorBuilder<Parent, Context> succeeder(const std::string& s = "")
        {
            auto child = std::make_shared<Succeeder<Context>>(s);
            node->SetChild(child);
            return DecoratorBuilder<Parent, Context>(parent, (Succeeder<Context>*)child.get());
        }

        // Repeater
        DecoratorBuilder<Parent, Context> repeater(const size_t n)
        {
            auto child = std::make_shared<Repeater<Context>>("", n);
            node->SetChild(child);
            return DecoratorBuilder<Parent, Context>(parent, (Repeater<Context>*)child.get());
        }

        // Repeater
        DecoratorBuilder<Parent, Context> repeater(const std::string& s, const size_t n)
        {
            auto child = std::make_shared<Repeater<Context>>(s, n);
            node->SetChild(child);
            return DecoratorBuilder<Parent, Context>(parent, (Repeater<Context>*)child.get());
        }

        // To add any other type of decorator
        template<
            typename DecoratorType,
            typename... Args,
            typename S,
            typename = typename std::enable_if_t<std::is_convertible_v<S, std::string>>
        >
        DecoratorBuilder<Parent, Context> decorator(const S& s, Args&&... args)
        {
            auto child = std::make_shared<DecoratorType>(s, std::forward<Args>(args)...);
            node->SetChild(child);
            return DecoratorBuilder<Parent, Context>(parent, (DecoratorType*)child.get());
        }
        template<
            typename DecoratorType,
            typename... Args
        >
        DecoratorBuilder<Parent, Context> decorator(Args&&... args)
        {
            auto child = std::make_shared<DecoratorType>("", std::forward<Args>(args)...);
            node->SetChild(child);
            return DecoratorBuilder<Parent, Context>(parent, (DecoratorType*)child.get());
        }

    private:
        Parent* parent;
        Decorator<Context>* node;
    };

    // Now that we have CompositeBuilder and DecoratorBuilder
    // we can define the main Builder class
    template<typename Context>
    class Builder
    {
    public:
        Builder(const std::string& name = "") : root(nullptr), root_name(name) {}

        template<
            typename S,
            typename... Args,
            typename = typename std::enable_if_t<std::is_convertible_v<S, std::string>>
        >
        std::shared_ptr<BehaviourTree<Context>> leaf(const S& s, Args&&... args)
        {
            auto tree = std::make_shared<BehaviourTree<Context> >(root_name);
            tree->SetRoot(std::make_shared<Leaf<Context> >(s, std::forward<Args>(args)...));
            return tree;
        }
        template<typename... Args>
        std::shared_ptr<BehaviourTree<Context>> leaf(Args&&... args)
        {
            auto tree = std::make_shared<BehaviourTree<Context> >(root_name);
            tree->SetRoot(std::make_shared<Leaf<Context> >("", std::forward<Args>(args)...));
            return tree;
        }


        // Composites
        // Custom function to add a sequence
        CompositeBuilder<Builder, Context> sequence(const std::string& s = "")
        {
            root = std::make_shared<Sequence<Context>>(s);
            return CompositeBuilder<Builder, Context>(this, (Sequence<Context>*)root.get());
        }

        // Custom function to add a selector
        CompositeBuilder<Builder, Context> selector(const std::string& s = "")
        {
            root = std::make_shared<Selector<Context>>(s);
            return CompositeBuilder<Builder, Context>(this, (Selector<Context>*)root.get());
        }

        // To add any other type of composite
        template<
            typename CompositeType,
            typename... Args,
            typename S,
            typename = typename std::enable_if_t<std::is_convertible_v<S, std::string>>
        >
        CompositeBuilder<Builder, Context> composite(const S& s, Args&&... args)
        {
            root = std::make_shared<CompositeType>(s, std::forward<Args>(args)...);
            return CompositeBuilder<Builder, Context>(this, (CompositeType*)root.get());
        }
        template<
            typename CompositeType,
            typename... Args
        >
        CompositeBuilder<Builder, Context> composite(Args&&... args)
        {
            root = std::make_shared<CompositeType>("", std::forward<Args>(args)...);
            return CompositeBuilder<Builder, Context>(this, (CompositeType*)root.get());
        }

        // Decorator
        // Inverter
        DecoratorBuilder<Builder, Context> inverter(const std::string& s = "")
        {
            root = std::make_shared<Inverter<Context>>(s);
            return DecoratorBuilder<Builder, Context>(this, (Inverter<Context>*)root.get());
        }

        // Succeeder
        DecoratorBuilder<Builder, Context> succeeder(const std::string& s = "")
        {
            root = std::make_shared<Succeeder<Context>>(s);
            return DecoratorBuilder<Builder, Context>(this, (Succeeder<Context>*)root.get());
        }

        // Repeater
        DecoratorBuilder<Builder, Context> repeater(const size_t n)
        {
            root = std::make_shared<Repeater<Context>>("", n);
            return DecoratorBuilder<Builder, Context>(this, (Repeater<Context>*)root.get());
        }

        // Repeater
        DecoratorBuilder<Builder, Context> repeater(const std::string& s, const size_t n)
        {
            root = std::make_shared<Repeater<Context>>(s, n);
            return DecoratorBuilder<Builder, Context>(this, (Repeater<Context>*)root.get());
        }

        // To add any other type of decorator
        template<
            typename DecoratorType,
            typename... Args,
            typename S,
            typename = typename std::enable_if_t<std::is_convertible_v<S, std::string>>
        >
        DecoratorBuilder<Builder, Context> decorator(const S& s, Args&&... args)
        {
            root = std::make_shared<DecoratorType>(s, std::forward<Args>(args)...);
            return DecoratorBuilder<Builder, Context>(this, (DecoratorType*)root.get());
        }
        template<
            typename DecoratorType,
            typename... Args
        >
        DecoratorBuilder<Builder, Context> decorator(Args&&... args)
        {
            root = std::make_shared<DecoratorType>("", std::forward<Args>(args)...);
            return DecoratorBuilder<Builder, Context>(this, (DecoratorType*)root.get());
        }

    private:
        std::shared_ptr<BehaviourTree<Context> > build()
        {
            auto tree = std::make_shared<BehaviourTree<Context> >(root_name);
            tree->SetRoot(root);
            return tree;
        }
        friend DecoratorBuilder<Builder, Context>;
        friend CompositeBuilder<Builder, Context>;

    private:
        const std::string root_name;
        std::shared_ptr<Node<Context> > root;
    };
} // namespace Botcraft
