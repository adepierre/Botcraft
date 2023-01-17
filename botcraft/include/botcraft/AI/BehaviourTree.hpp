#pragma once

#include <vector>
#include <memory>
#include <functional>

// A behaviour tree implementation following this blog article
// https://www.gamasutra.com/blogs/ChrisSimpson/20140717/221339/Behavior_trees_for_AI_How_they_work.php
// If you want the (more complete) original post rather than the new one:
// https://web.archive.org/web/20210826210308/https://www.gamasutra.com/blogs/ChrisSimpson/20140717/221339/Behavior_trees_for_AI_How_they_work.php

// Code inspired (especially for the builder part) by
// https://github.com/arvidsson/BrainTree

namespace Botcraft
{
    enum class Status
    {
        Failure,
        Success
    };

    template<class Context>
    class Node
    {
    public:
        Node() {}
        virtual ~Node() {}
        virtual const Status Tick(Context& context) const = 0;
    };


    template<class Context>
    class Composite : public Node<Context>
    {
    public:
        Composite() {}
        virtual ~Composite() {}

        void AddChild(const std::shared_ptr<Node<Context>>& child)
        {
            children.push_back(child);
        }

    protected:
        size_t GetNumChildren() const
        {
            return children.size();
        }

        // Needs to be virtual so we can access derived class to fetch
        // its real name and add it to exception message
        virtual Status TickChild(Context& context, const size_t index) const
        {
            if (index >= children.size())
            {
                throw std::runtime_error(std::string("Out of bounds child ticking in ") + typeid(*this).name() + " at index " + std::to_string(index));
            }

            if (children[index] == nullptr)
            {
                throw std::runtime_error(std::string("Nullptr child in ") + typeid(*this).name() + " at index " + std::to_string(index));
            }

            try
            {
                return children[index]->Tick(context);
            }
            catch (const std::exception& ex)
            {
                throw std::runtime_error(std::string("In ") + typeid(*this).name() + " while Ticking child " + std::to_string(index) + "\n" +
                    ex.what());
            }
        }

    private:
        std::vector<std::shared_ptr<Node<Context>>> children;
    };

    template<class Context>
    class Decorator : public Node<Context>
    {
    public:
        Decorator() { child = nullptr; }
        virtual ~Decorator() {}

        void SetChild(std::shared_ptr<Node<Context>> child_)
        {
            child = child_;
        }

        // Needs to be virtual so we can access derived class to fetch
        // its real name and add it to exception message
        virtual Status TickChild(Context& context) const
        {
            if (child == nullptr)
            {
                throw std::runtime_error("Nullptr child in decorator");
            }

            try
            {
                return child->Tick(context);
            }
            catch (const std::exception& ex)
            {
                throw std::runtime_error(std::string("In ") + typeid(*this).name() + "\n" +
                    ex.what());
            }
        }

    private:
        std::shared_ptr<Node<Context>> child;
    };

    template<class Context>
    class Leaf : public Node<Context>
    {
    public:
        Leaf() = delete;
        Leaf(const std::function<Status(Context&)>& func_)
        {
            func = func_;
        }

        template <class FunctionType, class... Args>
        Leaf(FunctionType func_, Args... args)
        {
            func = [=](Context& c) -> Status { return func_(c, (args)...); };
        }

        virtual ~Leaf() {}
        virtual const Status Tick(Context& context) const override
        {
            return func(context);
        }

    private:
        std::function<Status(Context&)> func;
    };

    template<class Context>
    class BehaviourTree : public Node<Context>
    {
    public:
        BehaviourTree() { root = nullptr; }
        virtual ~BehaviourTree() {}

        void SetRoot(const std::shared_ptr<Node<Context>> node) { root = node; }

        virtual const Status Tick(Context& context) const override
        {
            if (root == nullptr)
            {
                throw std::runtime_error(std::string("Nullptr tree when trying to tick ") + typeid(*this).name());
            }
            try
            {
                return root->Tick(context);
            }
            catch (const std::exception& ex)
            {
                throw std::runtime_error(std::string("In ") + typeid(*this).name() + "\n" +
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
    template<class Context>
    class Sequence : public Composite<Context>
    {
    public:
        virtual const Status Tick(Context& context) const override
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
    template<class Context>
    class Selector : public Composite<Context>
    {
    public:
        virtual const Status Tick(Context& context) const override
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
    template<class Context>
    class Inverter : public Decorator<Context>
    {
    public:
        virtual const Status Tick(Context& context) const override
        {
            return this->TickChild(context) == Status::Failure ? Status::Success : Status::Failure;
        }
    };

    /// @brief A Decorator that always return success,
    /// independently of the result of its child.
    /// Can be combined with an inverter for Failure.
    /// @tparam Context The tree context type
    template<class Context>
    class Succeeder : public Decorator<Context>
    {
    public:
        virtual const Status Tick(Context& context) const override
        {
            this->TickChild(context);
            return Status::Success;
        }
    };

    /// @brief A Decorator that ticks its child n times
    /// (repeat until first success if n == 0).
    /// Always returns success.
    /// @tparam Context The tree context type
    template<class Context>
    class Repeater : public Decorator<Context>
    {
    public:
        Repeater(const size_t n_)
        {
            n = n_;
        }

        virtual const Status Tick(Context& context) const override
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

    template <class Parent, class Context>
    class DecoratorBuilder;

    template <class Parent, class Context>
    class CompositeBuilder
    {
    public:
        CompositeBuilder(Parent* parent, Composite<Context>* node) : parent(parent), node(node) {}

        // To add a leaf
        template <class... Args>
        CompositeBuilder leaf(Args... args)
        {
            auto child = std::make_shared<Leaf<Context> >((args)...);
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
        CompositeBuilder<CompositeBuilder, Context> sequence()
        {
            auto child = std::make_shared<Sequence<Context>>();
            node->AddChild(child);
            return CompositeBuilder<CompositeBuilder, Context>(this, (Sequence<Context>*)child.get());
        }

        // Custom function to add a selector
        CompositeBuilder<CompositeBuilder, Context> selector()
        {
            auto child = std::make_shared<Selector<Context>>();
            node->AddChild(child);
            return CompositeBuilder<CompositeBuilder, Context>(this, (Selector<Context>*)child.get());
        }

        // To add any other type of composite
        template <class CompositeType, class... Args>
        CompositeBuilder<CompositeBuilder, Context> composite(Args... args)
        {
            auto child = std::make_shared<CompositeType>((args)...);
            node->AddChild(child);
            return CompositeBuilder<CompositeBuilder, Context>(this, (CompositeType*)child.get());
        }

        // Decorator
        // Inverter
        DecoratorBuilder<CompositeBuilder, Context> inverter()
        {
            auto child = std::make_shared<Inverter<Context>>();
            node->AddChild(child);
            return DecoratorBuilder<CompositeBuilder, Context>(this, (Inverter<Context>*)child.get());
        }

        // Succeeder
        DecoratorBuilder<CompositeBuilder, Context> succeeder()
        {
            auto child = std::make_shared<Succeeder<Context>>();
            node->AddChild(child);
            return DecoratorBuilder<CompositeBuilder, Context>(this, (Succeeder<Context>*)child.get());
        }

        // Repeater
        DecoratorBuilder<CompositeBuilder, Context> repeater(const size_t n)
        {
            auto child = std::make_shared<Repeater<Context>>(n);
            node->AddChild(child);
            return DecoratorBuilder<CompositeBuilder, Context>(this, (Repeater<Context>*)child.get());
        }

        // To add any other type of decorator
        template <class DecoratorType, class... Args>
        DecoratorBuilder<CompositeBuilder, Context> decorator(Args... args)
        {
            auto child = std::make_shared<DecoratorType>((args)...);
            node->AddChild(child);
            return DecoratorBuilder<CompositeBuilder, Context>(this, (DecoratorType*)child.get());
        }

        Parent& end()
        {
            return *parent;
        }

    private:
        Parent* parent;
        Composite<Context>* node;
    };

    template <class Parent, class Context>
    class DecoratorBuilder
    {
    public:
        DecoratorBuilder(Parent* parent, Decorator<Context>* node) : parent(parent), node(node) {}

        // To add a leaf
        template <typename... Args>
        DecoratorBuilder leaf(Args... args)
        {
            auto child = std::make_shared<Leaf<Context> >((args)...);
            node->SetChild(child);
            return *this;
        }

        // To add a tree
        DecoratorBuilder tree(std::shared_ptr<BehaviourTree<Context> > arg)
        {
            node->SetChild(arg);
            return *this;
        }


        // Composites
        // Custom function to add a sequence
        CompositeBuilder<DecoratorBuilder, Context> sequence()
        {
            auto child = std::make_shared<Sequence<Context>>();
            node->SetChild(child);
            return CompositeBuilder<DecoratorBuilder, Context>(this, (Sequence<Context>*)child.get());
        }

        // Custom function to add a selector
        CompositeBuilder<DecoratorBuilder, Context> selector()
        {
            auto child = std::make_shared<Selector<Context>>();
            node->SetChild(child);
            return CompositeBuilder<DecoratorBuilder, Context>(this, (Selector<Context>*)child.get());
        }

        // To add any other type of composite
        template <class CompositeType, class... Args>
        CompositeBuilder<DecoratorBuilder, Context> composite(Args... args)
        {
            auto child = std::make_shared<CompositeType>((args)...);
            node->SetChild(child);
            return CompositeBuilder<DecoratorBuilder, Context>(this, (CompositeType*)child.get());
        }

        // Decorator
        // Inverter
        DecoratorBuilder<DecoratorBuilder, Context> inverter()
        {
            auto child = std::make_shared<Inverter<Context>>();
            node->SetChild(child);
            return DecoratorBuilder<DecoratorBuilder, Context>(this, (Inverter<Context>*)child.get());
        }

        // Succeeder
        DecoratorBuilder<DecoratorBuilder, Context> succeeder()
        {
            auto child = std::make_shared<Succeeder<Context>>();
            node->SetChild(child);
            return DecoratorBuilder<DecoratorBuilder, Context>(this, (Succeeder<Context>*)child.get());
        }

        // Repeater
        DecoratorBuilder<DecoratorBuilder, Context> repeater(const size_t n)
        {
            auto child = std::make_shared<Repeater<Context>>(n);
            node->SetChild(child);
            return DecoratorBuilder<DecoratorBuilder, Context>(this, (Repeater<Context>*)child.get());
        }

        // To add any other type of decorator
        template <class DecoratorType, class... Args>
        DecoratorBuilder<DecoratorBuilder, Context> decorator(Args... args)
        {
            auto child = std::make_shared<DecoratorType>((args)...);
            node->SetChild(child);
            return DecoratorBuilder<DecoratorBuilder, Context>(this, (DecoratorType*)child.get());
        }

        Parent& end()
        {
            return *parent;
        }

    private:
        Parent* parent;
        Decorator<Context>* node;
    };

    // Now that we have CompositeBuilder and DecoratorBuilder
    // we can define the main Builder class
    template<class Context>
    class Builder
    {
    public:
        template <typename... Args>
        Builder leaf(Args... args)
        {
            root = std::make_shared<Leaf<Context> >((args)...);
            return *this;
        }

        // I'm not sure why someone would add a tree as the root of a tree but...
        Builder tree(std::shared_ptr<BehaviourTree<Context> > arg)
        {
            root = arg;
            return *this;
        }


        // Composites
        // Custom function to add a sequence
        CompositeBuilder<Builder, Context> sequence()
        {
            root = std::make_shared<Sequence<Context>>();
            return CompositeBuilder<Builder, Context>(this, (Sequence<Context>*)root.get());
        }

        // Custom function to add a selector
        CompositeBuilder<Builder, Context> selector()
        {
            root = std::make_shared<Selector<Context>>();
            return CompositeBuilder<Builder, Context>(this, (Selector<Context>*)root.get());
        }

        // To add any other type of composite
        template <class CompositeType, class... Args>
        CompositeBuilder<Builder, Context> composite(Args... args)
        {
            root = std::make_shared<CompositeType>((args)...);
            return CompositeBuilder<Builder, Context>(this, (CompositeType*)root.get());
        }

        // Decorator
        // Inverter
        DecoratorBuilder<Builder, Context> inverter()
        {
            root = std::make_shared<Inverter<Context>>();
            return DecoratorBuilder<Builder, Context>(this, (Inverter<Context>*)root.get());
        }

        // Succeeder
        DecoratorBuilder<Builder, Context> succeeder()
        {
            root = std::make_shared<Succeeder<Context>>();
            return DecoratorBuilder<Builder, Context>(this, (Succeeder<Context>*)root.get());
        }

        // Repeater
        DecoratorBuilder<Builder, Context> repeater(const size_t n)
        {
            root = std::make_shared<Repeater<Context>>(n);
            return DecoratorBuilder<Builder, Context>(this, (Repeater<Context>*)root.get());
        }

        // To add any other type of decorator
        template <class DecoratorType, class... Args>
        DecoratorBuilder<Builder, Context> decorator(Args... args)
        {
            root = std::make_shared<DecoratorType>((args)...);
            return DecoratorBuilder<Builder, Context>(this, (DecoratorType*)root.get());
        }

        std::shared_ptr<BehaviourTree<Context> > build()
        {
            auto tree = std::make_shared<BehaviourTree<Context> >();
            tree->SetRoot(root);
            return tree;
        }

    private:
        std::shared_ptr<Node<Context> > root;
    };
} // namespace Botcraft
