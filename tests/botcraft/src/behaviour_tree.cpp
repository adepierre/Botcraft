#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <botcraft/AI/BehaviourTree.hpp>

using namespace Botcraft;

Status TestLeaf(int& c)
{
    c += 1;
    return Status::Success;
}

Status TestLeafWithArg(int& c, const int i)
{
    c += i;
    return Status::Success;
}

TEST_CASE("LeafTree")
{
    int i = 0;
    SECTION("Function")
    {
        auto tree = Builder<int>()
            .leaf(TestLeaf)
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 1);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 2);
    }

    SECTION("FunctionWithArg")
    {
        auto tree = Builder<int>()
            .leaf(TestLeafWithArg, 2)
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 2);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 4);
    }

    SECTION("std::bind")
    {
        auto tree = Builder<int>()
            .leaf(std::bind(TestLeafWithArg, std::placeholders::_1, 2))
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 2);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 4);
    }

    SECTION("Lambda")
    {
        auto tree = Builder<int>()
            .leaf([](int& i) { i += 1; return Status::Success; })
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 1);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 2);
    }
}

template<class Context>
class CustomDecorator : public Decorator<Context>
{
public:
    virtual const Status Tick(Context& context) const override
    {
        this->TickChild(context);

        return Status::Failure;
    }
};
TEST_CASE("Decorator")
{
    int i = 0;
    SECTION("Inverter")
    {
        auto tree = Builder<int>()
            .inverter().leaf([](int& i) { i += 1; return Status::Success; })
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Failure);
        CHECK(i == 1);
        CHECK(tree->Tick(i) == Status::Failure);
        CHECK(i == 2);
    }

    SECTION("Succeeder")
    {
        auto tree = Builder<int>()
            .succeeder().leaf([](int& i) { i += 1; return Status::Failure; })
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 1);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 2);
    }

    SECTION("Repeater")
    {
        auto tree = Builder<int>()
            .repeater(3).leaf([](int& i) { i += 1; return Status::Success; })
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 3);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 6);

        i = 0;
        tree = Builder<int>()
            .repeater(0).leaf([](int& i) { i += 1; return i > 10 ? Status::Success : Status::Failure; })
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 11);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 12);
    }
    

    SECTION("CustomDecorator")
    {
        auto tree = Builder<int>()
            .decorator<CustomDecorator<int>>().leaf([](int& i) { i += 1; return Status::Success; })
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Failure);
        CHECK(i == 1);
        CHECK(tree->Tick(i) == Status::Failure);
        CHECK(i == 2);
    }
}


template<typename Context>
class CustomComposite : public Composite<Context>
{
public:
    virtual const Status Tick(Context& context) const override
    {
        for (size_t i = 0; i < GetNumChildren(); ++i)
        {
            this->TickChild(context, i);
        }

        return Status::Success;
    }
};
TEST_CASE("Composite")
{
    int i = 0;
    SECTION("Sequence")
    {
        auto tree = Builder<int>()
            .sequence()
                .leaf([](int& i) { i += 1; return Status::Success; })
                .leaf([](int& i) { i += 1; return Status::Failure; })
                .leaf([](int& i) { i += 1; return Status::Success; }) // Never reached
            .end()
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Failure);
        CHECK(i == 2);
        CHECK(tree->Tick(i) == Status::Failure);
        CHECK(i == 4);

        i = 0;
        tree = Builder<int>()
            .sequence()
                .leaf([](int& i) { i += 1; return Status::Success; })
                .leaf([](int& i) { i += 1; return Status::Success; })
                .leaf([](int& i) { i += 1; return Status::Success; })
            .end()
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 3);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 6);
    }

    SECTION("Empty")
    {
        auto tree = Builder<int>()
            .sequence() // empty sequence is useless but valid
            .end()
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 0);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 0);
    }

    SECTION("Selector")
    {
        auto tree = Builder<int>()
            .selector()
                .leaf([](int& i) { i += 1; return Status::Failure; })
                .leaf([](int& i) { i += 1; return Status::Failure; })
                .leaf([](int& i) { i += 1; return Status::Success; })
                .leaf([](int& i) { i += 1; return Status::Success; }) // Never reached
            .end()
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 3);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 6);

        i = 0;
        tree = Builder<int>()
            .selector()
                .leaf([](int& i) { i += 1; return Status::Failure; })
                .leaf([](int& i) { i += 1; return Status::Failure; })
                .leaf([](int& i) { i += 1; return Status::Failure; })
                .leaf([](int& i) { i += 1; return Status::Failure; })
            .end()
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Failure);
        CHECK(i == 4);
        CHECK(tree->Tick(i) == Status::Failure);
        CHECK(i == 8);
    }

    SECTION("CustomSelector")
    {
        auto tree = Builder<int>()
            .composite<CustomComposite<int>>()
                .leaf([](int& i) { i += 1; return Status::Success; })
                .leaf([](int& i) { i += 1; return Status::Failure; })
                .leaf([](int& i) { i += 1; return Status::Success; })
            .end()
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 3);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 6);
    }
}

TEST_CASE("Subtree")
{
    auto subtree = Builder<int>()
        .sequence()
            .leaf([](int& i) { i += 1; return Status::Success; })
            .leaf([](int& i) { i += 1; return Status::Failure; })
            .leaf([](int& i) { i += 1; return Status::Success; }) // Never reached
        .end()
        .build();

    auto tree = Builder<int>()
        .selector()
            .tree(subtree)
            .tree(subtree)
            .leaf([](int& i) { i += 1; return Status::Success; })
        .end()
        .build();

    int i = 0;
    CHECK_FALSE(tree == nullptr);
    CHECK(tree->Tick(i) == Status::Success);
    CHECK(i == 5);
    CHECK(tree->Tick(i) == Status::Success);
    CHECK(i == 10);
}

TEST_CASE("Exceptions")
{
    int i = 0;
    SECTION("Anonymous")
    {
        auto tree = Builder<int>()
            .sequence()
                .selector()
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                    .leaf([](int& i) { i += 1; return Status::Success; })
                .end()
                .selector()
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                    .composite<CustomComposite<int>>()
                        .leaf([](int& i) { i += 1; return Status::Failure; })
                        .leaf([](int& i) { i += 1; return Status::Failure; })
                        .leaf([](int& i) { i += 1; return Status::Failure; })
                        .leaf([](int& i) { i += 1; throw std::runtime_error("Exception to catch"); return Status::Failure; })
                    .end()
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                    .leaf([](int& i) { i += 1; return Status::Success; })
                .end()
            .end()
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK_THROWS(tree->Tick(i));
        CHECK(i == 11);

        try
        {
            tree->Tick(i);
        }
        catch (const std::exception& ex)
        {
            CHECK_THAT(ex.what(), Catch::Matchers::Equals(
                std::string("In ") + typeid(BehaviourTree<int>).name() + '\n' +
                "In " + typeid(Sequence<int>).name() + " while Ticking child 1\n" +
                "In " + typeid(Selector<int>).name() + " while Ticking child 2\n" +
                "In " + typeid(CustomComposite<int>).name() + " while Ticking child 3\n" +
                "Exception to catch")
            );
        }
    }
}

TEST_CASE("Nested")
{
    int i = 0;
    SECTION("Composite in Composite")
    {
        auto tree = Builder<int>()
            .sequence()
                .selector()
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                    .leaf([](int& i) { i += 1; return Status::Success; })
                .end()
                .selector()
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                    .composite<CustomComposite<int>>()
                        .leaf([](int& i) { i += 1; return Status::Failure; })
                        .leaf([](int& i) { i += 1; return Status::Failure; })
                        .leaf([](int& i) { i += 1; return Status::Failure; })
                        .leaf([](int& i) { i += 1; return Status::Failure; })
                    .end()
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                    .leaf([](int& i) { i += 1; return Status::Success; })
                .end()
            .end()
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 11);
    }

    SECTION("Composite in decorator")
    {
        auto tree = Builder<int>()
            .inverter().selector()
                .leaf([](int& i) { i += 1; return Status::Failure; })
                .leaf([](int& i) { i += 1; return Status::Failure; })
                .inverter().composite<CustomComposite<int>>()
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                    .leaf([](int& i) { i += 1; return Status::Failure; })
                .end()
                .leaf([](int& i) { i += 1; return Status::Failure; })
                .leaf([](int& i) { i += 1; return Status::Failure; })
            .end()
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 8);
    }

    SECTION("Decorator in decorator")
    {
        auto tree = Builder<int>()
            .inverter().decorator<CustomDecorator<int>>().repeater(3).leaf([](int& i) { i += 1; return Status::Success; })
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Success);
        CHECK(i == 3);
    }


    SECTION("Decorator in Composite")
    {
        auto tree = Builder<int>()
            .sequence()
                .inverter().leaf([](int& i) { i += 1; return Status::Failure; })
                .repeater(3).leaf([](int& i) { i += 1; return Status::Success; })
                .succeeder().leaf([](int& i) { i += 1; return Status::Failure; })
                .decorator<CustomDecorator<int>>().leaf([](int& i) { i += 1; return Status::Success; })
            .end()
            .build();

        CHECK_FALSE(tree == nullptr);
        CHECK(tree->Tick(i) == Status::Failure);
        CHECK(i == 6);
    }
}
