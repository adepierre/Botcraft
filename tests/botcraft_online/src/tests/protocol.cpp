#include "TestManager.hpp"
#include "MinecraftServer.hpp"
#include "Utils.hpp"

#include <catch2/catch_test_macros.hpp>

#include <atomic>

class RecipeListenerBot : public Botcraft::ManagersClient
{
public:
    RecipeListenerBot(const bool use_renderer_) : Botcraft::ManagersClient(use_renderer_) {}
    virtual ~RecipeListenerBot() {};

    std::atomic<bool> recipes_received;

protected:
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
    virtual void Handle(ProtocolCraft::ClientboundRecipePacket& packet) override { recipes_received = true; }
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    virtual void Handle(ProtocolCraft::ClientboundRecipeBookAddPacket& packet) override { recipes_received = true; }
#endif
};

TEST_CASE("recipes")
{
    std::unique_ptr<RecipeListenerBot> bot = SetupTestBot<RecipeListenerBot>();
    const std::string& botname = bot->GetNetworkManager()->GetMyName();
    // Wait for the initial recipe packet
    Botcraft::Utilities::WaitForCondition([&]() {
        return bot->recipes_received.load();
    }, 5000);
    // Reset status
    bot->recipes_received = false;
    // Ask the server to send all recipes
    MinecraftServer::GetInstance().SendLine("recipe give " + bot->GetNetworkManager()->GetMyName() + " *");
    MinecraftServer::GetInstance().WaitLine(".*recipe.*", 5000);
    REQUIRE(Botcraft::Utilities::WaitForCondition([&]() {
        return bot->recipes_received.load();
    }, 5000));
}
