#include <catch2/catch_test_macros.hpp>

#include <botcraft/AI/Blackboard.hpp>

using namespace Botcraft;

TEST_CASE("Blackboard Read/Write values")
{
    Blackboard blackboard;

    REQUIRE_NOTHROW(blackboard.Set("hello", std::string("world")));
    REQUIRE_NOTHROW(blackboard.Get<std::string>("hello"));
    REQUIRE(blackboard.Get<std::string>("hello") == "world");

    REQUIRE_NOTHROW(blackboard.Set("hello", 3));
    REQUIRE_THROWS(blackboard.Get<std::string>("hello"));
    REQUIRE(blackboard.Get<int>("hello") == 3);

    REQUIRE_NOTHROW(blackboard.Copy("hello", "world"));
    REQUIRE(blackboard.Get<int>("world") == 3);
    REQUIRE_THROWS(blackboard.Copy("hallo", "world"));

    REQUIRE_NOTHROW(blackboard.Erase("world"));
    REQUIRE_THROWS(blackboard.Get<int>("world"));

    NotifyOnEndUseRef<int> wrapped_ref = blackboard.GetRef<int>("hello", 42);
    int& ref = wrapped_ref.ref();
    REQUIRE(ref == 3);
    ref = 42;
    REQUIRE(ref == 42);
    REQUIRE(blackboard.Get<int>("hello") == 42);

    REQUIRE_NOTHROW(blackboard.Reset());
    REQUIRE_THROWS(blackboard.Get<int>("hello"));

    REQUIRE_NOTHROW(blackboard.Reset({ { "hello", 42 } }));
    REQUIRE(blackboard.Get<int>("hello") == 42);
}

class TestBlackboardObserver : public BlackboardObserver
{
public:
    void OnReset() override { is_reset = true; }
    void OnValueChanged(const std::string& key, const std::any& value) override { is_value_changed = true; }
    void OnValueRemoved(const std::string& key) override { is_value_removed = true; }

    bool is_reset = false;
    bool is_value_changed = false;
    bool is_value_removed = false;
};

TEST_CASE("Blackboard notifications")
{
    Blackboard blackboard;
    TestBlackboardObserver observer;
    blackboard.Subscribe(&observer);

    REQUIRE_FALSE(observer.is_reset);
    REQUIRE_FALSE(observer.is_value_changed);
    REQUIRE_FALSE(observer.is_value_removed);

    blackboard.Set<std::string>("hello", "world");
    REQUIRE(observer.is_value_changed);

    observer.is_value_changed = false;
    {
        const NotifyOnEndUseRef<std::string> wrapped_ref = blackboard.GetRef<std::string>("hello");
        std::string& ref = wrapped_ref.ref();
        ref = "world!";
    }
    REQUIRE(blackboard.Get<std::string>("hello") == "world!");
    REQUIRE(observer.is_value_changed);

    blackboard.Erase("hello");
    REQUIRE(observer.is_value_removed);

    blackboard.Reset();
    REQUIRE(observer.is_reset);
}
