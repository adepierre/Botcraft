#include <catch2/catch_test_macros.hpp>

#include <botcraft/Game/Entities/entities/entity.hpp>
#include <botcraft/Utilities/Logger.hpp>
#include <botcraft/Utilities/MiscUtilities.hpp>

TEST_CASE("All entities serialize")
{
    // Hide "unknown entity type" warning spam
    const Botcraft::LogLevel old_log_level = Botcraft::Logger::GetInstance().GetLogLevel();
    Botcraft::Utilities::OnEndScope reset_log_level([old_log_level]() { Botcraft::Logger::GetInstance().SetLogLevel(old_log_level); });
    Botcraft::Logger::GetInstance().SetLogLevel(Botcraft::LogLevel::Error);

    for (int i = 0; i < 1024; ++i)
    {
        std::shared_ptr<Botcraft::Entity> e = Botcraft::Entity::CreateEntity(static_cast<Botcraft::EntityType>(i));
        if (e->GetType() == Botcraft::EntityType::None)
        {
            continue;
        }
        INFO("Type: " << i);
        REQUIRE_NOTHROW(e->Serialize());
    }
}

TEST_CASE("All entities colliders")
{
    // Hide "unknown entity type" warning spam
    const Botcraft::LogLevel old_log_level = Botcraft::Logger::GetInstance().GetLogLevel();
    Botcraft::Utilities::OnEndScope reset_log_level([old_log_level]() { Botcraft::Logger::GetInstance().SetLogLevel(old_log_level); });
    Botcraft::Logger::GetInstance().SetLogLevel(Botcraft::LogLevel::Error);

    for (int i = 0; i < 1024; ++i)
    {
        std::shared_ptr<Botcraft::Entity> e = Botcraft::Entity::CreateEntity(static_cast<Botcraft::EntityType>(i));
        if (e->GetType() == Botcraft::EntityType::None)
        {
            continue;
        }
        INFO("Type: " << i);
        REQUIRE_NOTHROW(e->GetCollider());
    }
}
