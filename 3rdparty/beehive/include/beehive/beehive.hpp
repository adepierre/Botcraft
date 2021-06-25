#ifndef BEEHIVE_BEHAVIOR_TREE_HPP
#define BEEHIVE_BEHAVIOR_TREE_HPP

#include <algorithm>
#include <cassert>
#include <functional>
#include <iterator>
#include <thread>
#include <type_traits>
#include <vector>

/*!
 \file beehive.hpp
*/

namespace beehive
{

/*!
 \brief The status returned by process functions.
*/
enum class Status
{
    FAILURE = 0, //!< Returned when the process function has failed.
    RUNNING, //!< Returned when the outcome of process has not been determined yet.
    SUCCESS //!< Returns when the process has succeeded.
};

/*!
 \brief Pass a TreeState instance to #beehive::Tree's process function in order to resume Running nodes. Instantiate with #beehive::Tree::make_state. 
*/
struct TreeState {
    // For internal use only.
    size_t resume_index() const {
        return _resume_index;
    }
    // For internal use only.
    size_t offset() const {
        return _offset;
    }
private:
    TreeState(size_t tree_id): _tree_id(tree_id) {}
    
    size_t _tree_id;
    size_t _resume_index{};
    size_t _offset{};

    template<typename C, typename A>
    friend class Tree;
    template<typename C>
    friend struct Node;
};

/*!
 \brief A handle on a process function. This should not be built directly, see #beehive::Builder.
*/
template<typename C>
struct Node
{
    using ProcessFunction = std::function<Status(C &context, Node const &self, TreeState &state)>;

    Node(ProcessFunction process): _process(move(process)) {}

    Status process(C &context, TreeState &state) const
    {
        return _process(context, *this, state);
    }

    size_t child_count() const {
        return _child_count;
    }
    
    size_t descendant_count() const {
        // Only calculate on the first call
        if (_descendant_count == 0 && _child_count > 0) {
            _descendant_count = _child_count;
            auto *child = first_child();
            for (size_t i = 0; i < _child_count; ++i) {
                _descendant_count += child->descendant_count();
                child = child->next_sibling();
            }
        }
        return _descendant_count;
    }
    
    void add_child() {
        ++_child_count;
    }

    Node const *first_child() const {
        if (_child_count == 0) {
            return nullptr;
        }
        // Tree nodes are stored contiguously in depth-first order.
        // Therefore, first child is always current pointer plus 1.
        return this + 1;
    }
    
    Node const *next_sibling() const {
        // Tree nodes are stored contiguously in depth-first order.
        return this + descendant_count() + 1;
    }

    /*!
        \brief Returns this node's index in its tree. 
    */
    size_t index() const {
        return _index;
    }
    
    /*!
        \brief Updates the given tree state so that the tree can resume at this (composite) node with the child generator starting at the given child index. 
    */
    void save_state_at_child_index(TreeState &state, size_t child_index) const {
        state._resume_index = index();
        assert(child_index < child_count());
        state._offset = child_index;
    }

    /*!
        \brief Clears the given tree state so that subsequent process() calls do not resume. 
    */
    void clear_state(TreeState &state) const {
        state._resume_index = 0;
        state._offset = 0;
    }

private:
    template<typename Context, typename A>
    friend class Tree;
    
    size_t _index{};
    size_t _child_count{};
    mutable size_t _descendant_count{};
    ProcessFunction _process;
};

template<typename C>
using Generator = std::function<Node<C> const *()>;

/*!
 \brief Composites define how to run the process() function on the child range.
 
   The generator function returns the next child in the child array or nullptr after the
   end of the child array. If the previous call to process() returned RUNNING status,
   the first result of the generator will be the same child as was returned when the
   previous called returned the RUNNING status. This allows composites to resume
   where they left off.
   
   The child pointer returned is only valid within the scope of the composite function
   body.
*/
template<typename C>
using Composite = std::function<Status(C &, Generator<C> const &, TreeState &)>;

/*!
 \brief Composite that returns success if all children return success.
*/
template<typename C>
Status sequence(C &context, Generator<C> const &next_child, TreeState &state)
{
    while (auto const *child = next_child())
    {
        auto status = child->process(context, state);
        if (status != Status::SUCCESS)
        {
            return status;
        }
    }
    return Status::SUCCESS;
}

/*!
 \brief Composite that returns success on the first successful call.
*/
template<typename C>
Status selector(C &context, Generator<C> const &next_child, TreeState &state)
{
    while (auto const *child = next_child())
    {
        auto status = child->process(context, state);
        if (status != Status::FAILURE)
        {
            return status;
        }
    }
    return Status::FAILURE;
}

/*!
 \brief A decorator is a composite that may only have a single child.
*/
template<typename C>
using Decorator = std::function<Status(C &context, Node<C> const &child, TreeState &state)>;

/*!
 \brief Decorator that just returns the result of the child. Not very useful...
*/
template<typename C>
Status forwarder(C &context, Node<C> const &child, TreeState &state)
{
    return child.process(context, state);
}

/*!
 \brief Decorator that inverts the result of its child node.
*/
template<typename C>
Status inverter(C &context, Node<C> const &child, TreeState &state)
{
    const auto status = child.process(context, state);
    if (status == Status::RUNNING)
    {
        return status;
    }
    return status == Status::FAILURE ? Status::SUCCESS : Status::FAILURE;
}

/*!
 \brief Decorator that returns success regardless of the child result.
*/
template<typename C>
Status succeeder(C &context, Node<C> const &child, TreeState &state)
{
    child.process(context, state);
    return Status::SUCCESS;
}


template<typename ReturnType, typename ContextType>
using BasicLeaf = std::function<ReturnType(ContextType &context)>; //!< Leaf nodes are the `process()` function taking the mutable context and must return a status.

template<typename C>
using Leaf = BasicLeaf<Status, C>; //!< A Leaf function takes a Context & and returns a Status.

template<typename C>
using BoolLeaf = BasicLeaf<bool, C>; //!< A Leaf function returning bool returns SUCCESS on true and FAILURE on false. It is not possible to return RUNNING from such a function.

template<typename C>
using VoidLeaf = BasicLeaf<void, C>; //!< A Leaf function returning anything other than bool or Status can be added using #beehive::BuilderBase::void_leaf. The return value is ignored and SUCCESS is returned.

/*!
 \brief A leaf that always succeeds. Not very useful...
*/
template<typename C>
Status noop(C &)
{
    return Status::SUCCESS;
}

/*!
 \brief The behavior tree class which passes the ContextType around. See #beehive::Builder for making one.
*/
template<typename ContextType, typename A = std::allocator<Node<ContextType>>>
class Tree
{
public:
    using Context = ContextType;

    /*!
     \brief Process with the given context reference.
    */
    Status process(Context &context) const;

    /*!
     \brief Process with the given state and context reference.
    */
    Status process(TreeState &state, Context &context) const;

    /*!
     \brief Retrieves the nodes, for debugging purposes.
    */
    std::vector<Node<Context>, A> const &nodes() const {
        return _nodes;
    }

    /*!
     \brief Creates a state object that can be passed to subsequent process() calls. 
    */    
    TreeState make_state() const {  
        return {_id};
    }

private:
    static size_t id() {
        static size_t id{};
        return ++id;
    }

    template<typename C, typename Allocator>
    friend class BuilderBase;

    template<typename C, typename Allocator>
    friend class Builder;
    
    /*!
     \brief Constructs a tree with the given nodes.
        See #beehive::Builder.
    */
    Tree(std::vector<Node<Context>, A> nodes);

    std::vector<Node<Context>, A> _nodes;
    size_t _id{id()};
};

template<typename C, typename A>
Tree<C, A>::Tree(std::vector<Node<Context>, A> nodes)
    : _nodes(move(nodes))
{
    size_t i = 0;
    for (auto &node : _nodes) {
        node._index = i++; 
    }
}

template<typename C, typename A>
Status Tree<C, A>::process(Context &context) const
{
    TreeState state{_id};
    return _nodes[0].process(context, state);
}

template<typename C, typename A>
Status Tree<C, A>::process(TreeState &state, Context &context) const
{
    assert(state._tree_id == _id); // another tree's state used with this tree 
    return _nodes.at(state.resume_index()).process(context, state);
}

/// @cond
template<typename C>
auto make_branch(Decorator<C> f) -> typename Node<C>::ProcessFunction;

template<typename C>
auto make_branch(Composite<C> f) -> typename Node<C>::ProcessFunction;

template<typename C>
auto make_leaf(Leaf<C> f) -> typename Node<C>::ProcessFunction;

template<typename C>
auto make_leaf(VoidLeaf<C> f) -> typename Node<C>::ProcessFunction;

template<typename C>
auto make_leaf(BoolLeaf<C> f) -> typename Node<C>::ProcessFunction;
/// @endcond

template<typename C, typename A>
class Builder;

/*!
 \brief A helper for building trees which can be instantiated as #beehive::Builder.
*/
template<typename C, typename A>
class BuilderBase
{
public:
    /// @cond
    enum class Type
    {
        COMPOSITE,
        DECORATOR,
    };
    /// @endcond

    /*!
     \brief Adds the given composite to the tree. Composites have one or more children.

     \note The composite builder must call end() to signify end of child list.
    */
    BuilderBase composite(Composite<C> composite);

    /*!
     \brief Adds the given decorator to the tree. Decorators have exactly one child.
    
     \note The decorator builder must call end() to signify the end of the child list.
    */
    BuilderBase decorator(Decorator<C> decorator);
    
    // Note: "no known conversion" warnings here could indicate that you forgot to return something from your lambda.
    /*!
     \brief Adds the given leaf to the tree. Leaves have no children.
    */
    BuilderBase &leaf(Leaf<C> leaf);
    
    /*!
     \brief Convenience wrapper so that bool functions can be used. Translates true
        result to Status::SUCCESS, false to Status::FAILURE and never returns Status:RUNNING.
    */
    BuilderBase &leaf(BoolLeaf<C> leaf);

    /*!
     \brief Convenience wrapper for a void function, or really a function returning any type other than bool or Status. This always returns Status::SUCCESS.
    */
    BuilderBase &void_leaf(VoidLeaf<C> leaf);

    /*!
     \brief Copies another tree as a subtree at the current node.
    */
    BuilderBase &tree(Tree<C> const &subtree);
    
    /*!
     \brief Closes the composite or decorator branch.
     
        Each call to composite() or decorator() must have a corresponding end().
    */
    BuilderBase &end();

    /*!
     \brief Finalizes the tree by returning a copy. This will assert if done while
        a decorator or composite branch is still 'open'.
    */
    virtual Tree<C> build() const &;
    
    /*!
     \brief Finalizes the tree by returning a tree constructed with the builder's
        root node. The builder is then invalid.
    */
    virtual Tree<C> build() &&;

    /*!
     \brief Shorthand for `composite(&sequence<C>)`.
    */
    BuilderBase sequence();
    
    /*!
     \brief Shorthand for `composite(&selector<C>)`.
    */
    BuilderBase selector();

    /*!
     \brief Shorthand for `decorator(&inverter<C>)`.
    */
    BuilderBase inverter();

    /*!
     \brief Shorthand for `decorator(&succeeder<C>)`.
    */
    BuilderBase succeeder();

protected:
    /// @cond
    BuilderBase(BuilderBase &parent, size_t offset, Type type)
        : _parent(parent)
        , _offset(offset)
        , _type(type)
    {}

    Node<C> &node() {
        return nodes()[_offset];
    }
    
    virtual std::vector<Node<C>, A> &nodes() {
        return _parent.nodes();
    }

private:
    size_t add_child(typename Node<C>::ProcessFunction &&fn) {
        node().add_child();
        nodes().emplace_back(std::move(fn));
        return nodes().size() - 1;
    }

    template<typename LeafType>
    BuilderBase &_leaf(LeafType &&leaf);

    template<typename BranchType>
    BuilderBase _branch(BranchType &&branch);

    BuilderBase &_parent;
    size_t _offset{};
    Type _type{};

    /// @endcond
};

/*!
 \brief Defines the tree structure and instantiates it.
 
    This Builder pattern is inspired by arvidsson's implementation, BrainTree.
 \sa #beehive::BuilderBase
*/
template<typename C, typename Allocator = std::allocator<Node<C>>>
class Builder
    : public BuilderBase<C, Allocator>
{
public:
    /*!
     \brief The context type.
    */
    using Context = C;

    /*!
     \brief Begins construction of a tree.
    */
    Builder()
        : BuilderBase<C, Allocator>(*this, 0, BuilderBase<C, Allocator>::Type::DECORATOR)
    {
        auto root = make_branch(Decorator<C>(&forwarder<C>));
        _nodes.emplace_back(std::move(root));
    }
    
    Builder(Builder const &) = delete; //!< Deleted copy constructor.
    Builder(Builder &&) = default; //!< Move constructor.
    Builder &operator=(Builder const &) = delete; //!< Deleted copy assignment operator.
    Builder &operator=(Builder &&) = default; //!< Move assignment operator.

    virtual Tree<C> build() const & override
    {
        assert(_nodes[0].child_count() > 0); // must have at least one leaf node added
        return {_nodes};
    }

    virtual Tree<C> build() && override
    {
        assert(_nodes[0].child_count() > 0); // must have at least one leaf node added
        return {std::move(_nodes)};
    }

private:
    virtual std::vector<Node<C>, Allocator> &nodes() override {
        return _nodes;
    }
    
    std::vector<Node<C>, Allocator> _nodes;
};

/// @cond
template<typename C>
auto make_branch(Decorator<C> f) -> typename Node<C>::ProcessFunction
{
    return [process = move(f)](C &context, Node<C> const &self, TreeState &state)
    {
        assert(self.child_count() == 1); // invariant violation!
        auto &child = *(&self + 1);
        return process(context, child, state);
    };
}

template<typename C>
auto make_branch(Composite<C> f) -> typename Node<C>::ProcessFunction
{
    return [process = move(f)](C &context, Node<C> const &self, TreeState &state)
    {
        auto i = 0;
        auto *child = self.first_child();
        if (self.index() == state.resume_index()) {
            for (; i < state.offset(); ++i) {
                child = child->next_sibling();
            }
        }
        auto generator = [&self, &i, &child]() -> Node<C> const * {
            if (i++ == self.child_count()) {
                return nullptr;
            }
            auto c = child;
            child = child->next_sibling();
            return c;
        };
        auto status = process(context, generator, state);
        if (status == Status::RUNNING) {
            self.save_state_at_child_index(state, i - 1);
        } else {
            self.clear_state(state);
        }
        return status;
    };
}

template<typename C>
auto make_leaf(Leaf<C> f) -> typename Node<C>::ProcessFunction
{
    return [process = move(f)](C &context, Node<C> const &self, TreeState &state)
    {
        assert(self.child_count() == 0); // invariant violation!
        return process(context);
    };
}

template<typename C>
auto make_leaf(VoidLeaf<C> f) -> typename Node<C>::ProcessFunction
{
    return make_leaf(Leaf<C>{[void_process = move(f)](C &context)
    {
        void_process(context);
        return Status::SUCCESS;
    }});
}

template<typename C>
auto make_leaf(BoolLeaf<C> f) -> typename Node<C>::ProcessFunction
{
    return make_leaf(Leaf<C>{[bool_process = move(f)](C &context)
    {
        const bool result = bool_process(context);
        return result ? Status::SUCCESS : Status::FAILURE;
    }});
}

template<typename C, typename A>
auto BuilderBase<C, A>::composite(Composite<C> composite) -> BuilderBase
{
    return _branch(std::move(composite));
}

template<typename C, typename A>
auto BuilderBase<C, A>::decorator(Decorator<C> decorator) -> BuilderBase
{
    return _branch(std::move(decorator));
}

template<typename C, typename A>
template<typename BranchType>
auto BuilderBase<C, A>::_branch(BranchType &&branch) -> BuilderBase
{
    assert((_type != Type::DECORATOR) || node().child_count() == 0); // Decorators may only have one child!
    auto type = std::is_same<
        typename std::decay<BranchType>::type,
        Decorator<C>
    >::value ? Type::DECORATOR : Type::COMPOSITE;
    auto child_offset = add_child(make_branch(move(branch)));
    return {*this, child_offset, type};
}

template<typename C, typename A>
template<typename LeafType>
auto BuilderBase<C, A>::_leaf(LeafType &&leaf) -> BuilderBase &
{
    assert((_type != Type::DECORATOR) || node().child_count() == 0); // Decorators may only have one child!
    add_child(make_leaf(move(leaf)));
    return *this;
}

template<typename C, typename A>
auto BuilderBase<C, A>::leaf(Leaf<C> leaf) -> BuilderBase &
{
    return _leaf(std::move(leaf));
}

template<typename C, typename A>
auto BuilderBase<C, A>::leaf(BoolLeaf<C> leaf) -> BuilderBase &
{
    return _leaf(std::move(leaf));
}

template<typename C, typename A>
auto BuilderBase<C, A>::void_leaf(VoidLeaf<C> leaf) -> BuilderBase &
{
    return _leaf(std::move(leaf));
}

template<typename C, typename A>
auto BuilderBase<C, A>::tree(Tree<C> const &subtree) -> BuilderBase &
{
    assert((_type != Type::DECORATOR) || node().child_count() == 0); // Decorators may only have one child!
    auto const &subtree_nodes = subtree.nodes();
    copy(subtree_nodes.begin(), subtree_nodes.end(), back_inserter(nodes()));
    node().add_child();
    return *this;
}

template<typename C, typename A>
auto BuilderBase<C, A>::end() -> BuilderBase &
{
    assert(node().child_count() > 0); // can't have composite/decorator without children!
    return _parent;
}

template<typename C, typename A>
auto BuilderBase<C, A>::build() const & -> Tree<C>
{
    assert(false); // unterminated tree!
    return {{}};
}

template<typename C, typename A>
auto BuilderBase<C, A>::build() && -> Tree<C>
{
    assert(false); // unterminated tree!
    return {{}};
}

#define BH_IMPLEMENT_SHORTHAND(Type, Name) \
    template<typename Context, typename A> \
    auto BuilderBase<Context, A>::Name() -> BuilderBase \
    { \
        return _branch(Type<Context>{&beehive::Name<Context>}); \
    }

BH_IMPLEMENT_SHORTHAND(Composite, sequence);
BH_IMPLEMENT_SHORTHAND(Composite, selector);
BH_IMPLEMENT_SHORTHAND(Decorator, inverter);
BH_IMPLEMENT_SHORTHAND(Decorator, succeeder);

#undef BH_IMPLEMENT_SHORTHAND
/// @endcond

} // namespace beehive

#endif
