#include "TestManager.hpp"
#include "Utils.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <botcraft/Game/Entities/LocalPlayer.hpp>
#include <botcraft/Utilities/SleepUtilities.hpp>
#include <botcraft/Version.hpp>

#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace Botcraft;

void TestPhysicsTrajectory(const std::string& test_name);

static const std::vector<double> precision_check = { 1e-3, 1e-6 };

// Physics tests requiring tick-precision accuracy are marked as mayfail
// as they can potentially break because of bad thread timing
// They also don't run by default, and need the [.physics] tag to
// be set in the command line
#define PHYSICS_TEST_CASE(Name) TEST_CASE(Name, "[!mayfail][.physics]") { TestPhysicsTrajectory(Name); } static_assert("forcing ;")

// Would be cool if we could just automatically have one test per file in the folder
// but I don't think it's possible to register tests at runtime with Catch2 :(
// So instead we need to manually add each trajectory file here
PHYSICS_TEST_CASE("fall on");

PHYSICS_TEST_CASE("walk on concrete");

PHYSICS_TEST_CASE("walk on concrete#sprint");

PHYSICS_TEST_CASE("walk on concrete#sneak");

PHYSICS_TEST_CASE("walk on concrete#jump");

PHYSICS_TEST_CASE("walk on ice");

PHYSICS_TEST_CASE("walk on soul sand");

PHYSICS_TEST_CASE("jump bump");

PHYSICS_TEST_CASE("block transition");

PHYSICS_TEST_CASE("collisions");

// NON TRAJECTORY TESTS BELOW

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
TEST_CASE("tick rate jump")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();

    double tick_rate = 0.0;
    double expected_time_ms = 0.0;

    SECTION("20")
    {
        tick_rate = 20.0;
        expected_time_ms = 50.0 * 12;
    }

    SECTION("10")
    {
        tick_rate = 10.0;
        expected_time_ms = 100.0 * 12;
    }

    SECTION("40")
    {
        tick_rate = 40.0;
        // Speeding up the tick rate does not speed up the physics
        expected_time_ms = 50.0 * 12;
    }

    MinecraftServer::GetInstance().SendLine("tick rate " + std::to_string(tick_rate));
    MinecraftServer::GetInstance().WaitLine(".*: Set the target tick rate to.*", 5000);

    // Wait for the bot to be on the ground
    Utilities::WaitForCondition([&]() {
        return bot->GetLocalPlayer() != nullptr && bot->GetLocalPlayer()->GetOnGround();
    }, 5000);

    auto start = std::chrono::steady_clock::now();
    bot->GetLocalPlayer()->SetInputsJump(true);
    // Wait for the bot to not be on the ground anymore
    Utilities::WaitForCondition([&]() {
        return !bot->GetLocalPlayer()->GetOnGround();
    }, 5000);
    // Wait for the bot to be back on the ground
    Utilities::WaitForCondition([&]() {
        return bot->GetLocalPlayer()->GetOnGround();
    }, 5000);
    auto end = std::chrono::steady_clock::now();

    const double elapsed_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    CHECK_THAT(elapsed_time_ms, Catch::Matchers::WithinAbs(expected_time_ms, 200));

    // Reset tickrate
    MinecraftServer::GetInstance().SendLine("tick rate 20");
    MinecraftServer::GetInstance().WaitLine(".*: Set the target tick rate to.*", 5000);
}
#endif

TEST_CASE("elytra rocket boost")
{
    std::unique_ptr<SimpleBehaviourClient> bot = SetupTestBot<SimpleBehaviourClient>();
    const std::string& botname = bot->GetNetworkManager()->GetMyName();
    std::shared_ptr<InventoryManager> inventory_manager = bot->GetInventoryManager();
    std::shared_ptr<LocalPlayer> player = bot->GetLocalPlayer();
    const ItemId elytra_id = AssetsManager::getInstance().GetItemID("minecraft:elytra");
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    const ItemId firework_id = AssetsManager::getInstance().GetItemID("minecraft:firework_rocket");
#else
    const ItemId firework_id = AssetsManager::getInstance().GetItemID("minecraft:fireworks");
#endif

    SendCommandSetItem(botname, "minecraft:elytra", EquipmentSlot::ChestPlate);
    // Wait for chestplate to be elytra
    CHECK(Utilities::WaitForCondition([&]() {
        return inventory_manager->GetPlayerInventory()->GetSlot(Window::INVENTORY_CHEST_ARMOR).GetItemId() == elytra_id;
    }, 5000));
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    SendCommandSetItem(botname, "minecraft:firework_rocket", EquipmentSlot::MainHand);
#else
    SendCommandSetItem(botname, "minecraft:fireworks", EquipmentSlot::MainHand);
#endif
    // Wait for main hand to be a rocket
    CHECK(Utilities::WaitForCondition([&]() {
        return inventory_manager->GetPlayerInventory()->GetSlot(Window::INVENTORY_HOTBAR_START).GetItemId() == firework_id;
    }, 5000));

    // Jump and wait for going up then falling back to trigger elytra flying mode
    player->SetInputsJump(true);
    Utilities::WaitForCondition([&]() -> bool {
        if (player->GetDirtyInputs())
        {
            return false;
        }
        player->SetInputsJump(false);
        return player->GetSpeedY() > 0.0;
    }, 1500);
    Utilities::WaitForCondition([&]() -> bool {
        if (player->GetDirtyInputs())
        {
            return false;
        }
        player->SetInputsJump(false);
        return player->GetSpeedY() < 0.0;
    }, 1500);
    player->SetInputsJump(true);
    // Wait for fly mode to start
    REQUIRE(Utilities::WaitForCondition([&]() {
        return player->GetDataSharedFlagsId(EntitySharedFlagsId::FallFlying);
    }, 5000));

    float previous_z_speed = player->GetSpeedZ();

    std::shared_ptr<ProtocolCraft::ServerboundUseItemPacket> use_item_packet = std::make_shared<ProtocolCraft::ServerboundUseItemPacket>();
    use_item_packet->SetHand(static_cast<int>(Hand::Main));
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    use_item_packet->SetSequence(bot->GetWorld()->GetNextWorldInteractionSequenceId());
#endif
    bot->GetNetworkManager()->Send(use_item_packet);

    // Wait for a big speed boost on Z axis
    REQUIRE(Utilities::WaitForCondition([&]() {
        if (player->GetDirtyInputs())
        {
            return false;
        }
        player->SetInputsJump(false);
        const float current_speed = player->GetSpeedZ();
        if (current_speed - previous_z_speed > 0.5)
        {
            return true;
        }
        previous_z_speed = current_speed;
        return false;
    }, 5000));
}

std::vector<int> StrVersionToVectorInt(const std::string& version)
{
    std::string token;
    std::vector<int> output;

    std::stringstream s(version);

    while (std::getline(s, token, '.'))
    {
        output.push_back(std::stoi(token));
    }
    return output;
}

void TestPhysicsTrajectory(const std::string& test_name)
{
    static std::string current_test = "";

    const Position& test_offset = TestManager::GetInstance().GetCurrentOffset();

    const std::filesystem::path traj_path = std::filesystem::path("test_server_files") / "runtime" / "physics_trajectories" / "vanilla" / game_version / (ReplaceCharacters(test_name, {{' ', "_"}}) + ".traj");
    if (!std::filesystem::exists(traj_path))
    {
        SKIP("missing trajectory file");
    }

    std::ifstream file(traj_path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    std::string line;
    std::string test_min_version;
    std::string test_max_version;
    std::getline(buffer, test_min_version);
    std::getline(buffer, test_max_version);
    if ((!test_min_version.empty() && StrVersionToVectorInt(game_version) < StrVersionToVectorInt(test_min_version)) ||
        (!test_max_version.empty() && StrVersionToVectorInt(game_version) > StrVersionToVectorInt(test_max_version))
    )
    {
        SKIP("skipped for version " + game_version);
    }


    std::string section_name;
    while (std::getline(buffer, section_name))
    {
        // Read section header
        std::string section_min_version;
        std::string section_max_version;
        std::string gamemode_str;
        std::string tp_offsets_str;
        std::string commands_pre_run;
        std::string commands_post_run;
        std::string csv_key_header;
        std::getline(buffer, section_min_version);
        std::getline(buffer, section_max_version);
        std::getline(buffer, gamemode_str);
        std::getline(buffer, tp_offsets_str);
        std::getline(buffer, commands_pre_run);
        std::getline(buffer, commands_post_run);
        std::getline(buffer, csv_key_header);
        const bool keep_section =
            (section_min_version.empty() || StrVersionToVectorInt(game_version) >= StrVersionToVectorInt(section_min_version)) &&
            (section_max_version.empty() || StrVersionToVectorInt(game_version) <= StrVersionToVectorInt(section_max_version));

        // Read all trajectory ticks
        std::vector<std::string> section_lines;
        while (std::getline(buffer, line))
        {
            if (line.empty())
            {
                break;
            }
            if (keep_section)
            {
                section_lines.push_back(line);
            }
        }
        // Go back to main loop to read next section header
        // (should not happen if the trajectory has been
        // generated with the same version)
        if (!keep_section)
        {
            continue;
        }

        // Process the section lines
        SECTION(section_name)
        {
            std::ofstream trajectory_file(std::filesystem::path("test_server_files") / "runtime" / "physics_trajectories" / "botcraft" / game_version / (ReplaceCharacters(test_name, { {' ', "_"} }) + ".traj"), std::ios::app);
            std::ofstream recap_file(TestManager::GetInstance().GetPhysicsRecapPath(), std::ios::app);
            // Only write min/max test version the first time this test actually runs
            if (current_test != test_name)
            {
                trajectory_file << test_min_version << '\n';
                trajectory_file << test_max_version << '\n';
                recap_file << "\n\n#### " << test_name << "\n\n";
                recap_file << "|  |";
                for (const auto d : precision_check)
                {
                    recap_file << ' ' << std::scientific << std::setprecision(0) << d << " |";
                }
                recap_file << '\n';
                recap_file << "|---|";
                for (const auto d : precision_check)
                {
                    recap_file << "---|";
                }
                recap_file << '\n';
                current_test = test_name;
            }

            trajectory_file << section_name        << '\n';
            trajectory_file << section_min_version << '\n';
            trajectory_file << section_max_version << '\n';
            trajectory_file << gamemode_str        << '\n';
            trajectory_file << tp_offsets_str      << '\n';
            trajectory_file << commands_pre_run    << '\n';
            trajectory_file << commands_post_run   << '\n';
            trajectory_file << csv_key_header      << '\n';
            recap_file << "| " << section_name << " |";

            char delimiter;

            GameType gamemode= GameType::None;
            if (gamemode_str == "survival")
            {
                gamemode = GameType::Survival;
            }
            else if (gamemode_str == "creative")
            {
                gamemode = GameType::Creative;
            }
            else if (gamemode_str == "spectator")
            {
                gamemode = GameType::Spectator;
            }
            else if (gamemode_str == "adventure")
            {
                gamemode = GameType::Adventure;
            }
            else
            {
                throw std::runtime_error("Unknown gamemode: " + gamemode_str);
            }

            std::istringstream offset_stream(tp_offsets_str);
            Vector3<double> tp_offset;
            float tp_yaw, tp_pitch;
            offset_stream    >> tp_offset.x
                >> delimiter >> tp_offset.y
                >> delimiter >> tp_offset.z
                >> delimiter >> tp_yaw
                >> delimiter >> tp_pitch;

            // TODO: Parse the csv header to get the order of the fields.
            // As the file is generated automatically, I guess we can assume the
            // order won't change randomly so not a priority

            std::vector<PlayerInputs> keyboard_inputs(section_lines.size());
            std::vector<std::pair<float, float>> rotation_inputs(section_lines.size());
            std::vector<Vector3<double>> vanilla_positions(section_lines.size());
            std::vector<bool> vanilla_on_ground(section_lines.size());
            size_t line_index = 0;
            for (const auto& l : section_lines)
            {
                std::istringstream line_stream(l);
                bool forward, left, backward, right, ground;
                line_stream      >> forward
                    >> delimiter >> left
                    >> delimiter >> backward
                    >> delimiter >> right
                    >> delimiter >> keyboard_inputs[line_index].jump
                    >> delimiter >> keyboard_inputs[line_index].sneak
                    >> delimiter >> keyboard_inputs[line_index].sprint
                    >> delimiter >> rotation_inputs[line_index].first
                    >> delimiter >> rotation_inputs[line_index].second
                    >> delimiter >> vanilla_positions[line_index].x
                    >> delimiter >> vanilla_positions[line_index].y
                    >> delimiter >> vanilla_positions[line_index].z
                    >> delimiter >> ground;
                keyboard_inputs[line_index].forward_axis = 1.0f * forward - 1.0f * backward;
                keyboard_inputs[line_index].left_axis = 1.0f * left - 1.0f * right;
                vanilla_on_ground[line_index] = ground;
                line_index += 1;
            }

            // Create the bot
            std::unique_ptr<ManagersClient> bot = SetupTestBot(tp_offset, gamemode, tp_yaw, tp_pitch);
            const std::string& bot_name = bot->GetNetworkManager()->GetMyName();
            std::shared_ptr<LocalPlayer> local_player = bot->GetLocalPlayer();
            static constexpr std::string_view player_name_pattern = "${PLAYER_NAME}";

            // run pre-run commands
            std::string command, regex;
            std::istringstream commands_pre_run_stream(commands_pre_run);
            while (std::getline(commands_pre_run_stream, command, ';'))
            {
                // Replace all "${PLAYER_NAME}" occurences with the actual player name in the command
                size_t pos = 0;
                while ((pos = command.find(player_name_pattern.data(), pos)) != std::string::npos)
                {
                    command.replace(pos, player_name_pattern.size(), bot_name);
                    pos += bot_name.size();
                }
                std::getline(commands_pre_run_stream, regex, ';');
                pos = 0;
                while ((pos = regex.find(player_name_pattern.data(), pos)) != std::string::npos)
                {
                    regex.replace(pos, player_name_pattern.size(), bot_name);
                    pos += bot_name.size();
                }

                MinecraftServer::GetInstance().SendLine(command);
                MinecraftServer::GetInstance().WaitLine(regex, 5000);
            }

            std::vector<Vector3<double>> botcraft_positions(section_lines.size());
            std::vector<bool> botcraft_on_ground(section_lines.size());

            // Wait for a couple of ticks to reduce the risk of something not being registered
            for (int i = 0; i < 2; ++i)
            {
                local_player->SetInputsJump(false);
                Utilities::WaitForCondition([&]() -> bool {
                    return !local_player->GetDirtyInputs();
                }, 150);
            }

            // Run the full trajectory
            for (size_t i = 0; i < section_lines.size(); ++i)
            {
                local_player->SetInputs(keyboard_inputs[i]);
                local_player->SetYaw(rotation_inputs[i].first);
                local_player->SetPitch(rotation_inputs[i].second);
                Utilities::WaitForCondition([&]() -> bool {
                    return !local_player->GetDirtyInputs();
                }, 150);
                botcraft_positions[i] = local_player->GetPosition() - test_offset;
                botcraft_on_ground[i] = local_player->GetOnGround();
            }

            // run post-run commands
            std::istringstream commands_post_run_stream(commands_post_run);
            while (std::getline(commands_post_run_stream, command, ';'))
            {
                // Replace all "${PLAYER_NAME}" occurences with the actual player name in the command
                size_t pos = 0;
                while ((pos = command.find(player_name_pattern.data(), pos)) != std::string::npos)
                {
                    command.replace(pos, player_name_pattern.size(), bot_name);
                    pos += bot_name.size();
                }
                std::getline(commands_post_run_stream, regex, ';');
                pos = 0;
                while ((pos = regex.find(player_name_pattern.data(), pos)) != std::string::npos)
                {
                    regex.replace(pos, player_name_pattern.size(), bot_name);
                    pos += bot_name.size();
                }

                MinecraftServer::GetInstance().SendLine(command);
                MinecraftServer::GetInstance().WaitLine(regex, 5000);
            }

            std::vector<bool> validate_precision(precision_check.size(), true);
            for (size_t i = 0; i < section_lines.size(); ++i)
            {
                const double position_error = std::sqrt((vanilla_positions[i] - botcraft_positions[i]).SqrNorm());
                for (size_t j = 0; j < precision_check.size(); ++j)
                {
                    validate_precision[j] =
                        validate_precision[j] &&
                        position_error < precision_check[j] &&
                        vanilla_on_ground[i] == botcraft_on_ground[i];
                }
            }

            // Write report and trajectory files
            for (const bool b : validate_precision)
            {
                recap_file << ' ' << (b ? "\xE2\x9C\x94" /* green checkmark */ : "\xE2\x9D\x8C" /* red cross */) << " |";
            }
            recap_file << '\n';

            for (size_t i = 0; i < section_lines.size(); ++i)
            {
                trajectory_file << std::setprecision(16)
                           << (keyboard_inputs[i].forward_axis > 0.5f)
                    << ';' << (keyboard_inputs[i].left_axis > 0.5f)
                    << ';' << (keyboard_inputs[i].forward_axis < -0.5f)
                    << ';' << (keyboard_inputs[i].left_axis < -0.5f)
                    << ';' << keyboard_inputs[i].jump
                    << ';' << keyboard_inputs[i].sneak
                    << ';' << keyboard_inputs[i].sprint
                    << ';' << rotation_inputs[i].first
                    << ';' << rotation_inputs[i].second
                    << ';' << botcraft_positions[i].x
                    << ';' << botcraft_positions[i].y
                    << ';' << botcraft_positions[i].z
                    << ';' << botcraft_on_ground[i]
                    << '\n';
            }
            trajectory_file << '\n';

            // Compare botcraft trajectory to the vanilla one
            for (size_t i = 0; i < section_lines.size(); ++i)
            {
                // Convert absolute recorded position to relative position wrt the bottom right corner of the structure block
                INFO(section_name);
                INFO("Tick " << i);
                INFO("Vanilla: " << vanilla_positions[i] << " " << vanilla_on_ground[i] << " | Botcraft: " << botcraft_positions[i] << " " << botcraft_on_ground[i]);
                const double position_error = std::sqrt((vanilla_positions[i] - botcraft_positions[i]).SqrNorm());
                REQUIRE_THAT(position_error, Catch::Matchers::WithinAbs(0.0, 1e-6));
                REQUIRE(vanilla_on_ground[i] == botcraft_on_ground[i]);
            }
        }
    }
}
