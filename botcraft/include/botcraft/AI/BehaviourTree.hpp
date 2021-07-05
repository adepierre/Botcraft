#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <thread>
#include <future>
#include <mutex>

// A simple behaviour tree implementation following this blog article
// https://www.gamasutra.com/blogs/ChrisSimpson/20140717/221339/Behavior_trees_for_AI_How_they_work.php

namespace Botcraft::BT
{
	enum class Status
	{
		Failure,
		Running,
		Success
	};

	template<typename C>
	class Node
	{
	public:
		Node() {}
		virtual ~Node() {}
		virtual const Status Tick(C& context) = 0;
	};


	template<typename C>
	class Composite : public Node<C>
	{
	public:
		Composite() {}
		virtual ~Composite() {}

		void AddChild(std::shared_ptr<Node<C>> child) 
		{
			children.push_back(child);
		}

	protected:
		std::vector<std::shared_ptr<Node<C>>> children;
		std::vector<std::shared_ptr<Node<C>>>::iterator it;
	};

	template<typename C>
	class Decorator : public Node<C>
	{
	public:
		Decorator() { child = nullptr; }
		virtual ~Decorator() {}

		void SetChild(std::shared_ptr<Node<C>> child_) 
		{ 
			child = child_;
		}

	protected:
		std::shared_ptr<Node<C>> child;
	};

	template<typename C>
	class Leaf : public Node<C>
	{
	public:
		Leaf() = delete;
		Leaf(std::function<Status(C&)> func_)
		{
			func = func_;
		}
		virtual ~Leaf() {}
		virtual const Status Tick(C& context) override
		{
			return func(context);
		}

	private:
		std::function<Status(C&)> func;
	};

	class InterruptedException : public std::exception
	{

	};

	template<typename C>
	class BehaviourTree : public Node<C>
	{
	public:
		BehaviourTree() { root = nullptr; }
		virtual ~BehaviourTree() {}

		void SetRoot(const std::shared_ptr<Node<C>> node) { root = node; }
		
		virtual const Status Tick(C& context) override
		{
			if (root == nullptr)
			{
				return Status::Failure;
			}
			return root->Tick();
		}

	private:
		std::shared_ptr<Node<C>> root;
	};

} // namespace Botcraft::BT