#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>

#include "botcraft/Game/World/World.hpp"
#include "botcraft/Game/World/Block.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Network/NetworkManager.hpp"

#include "botcraft/AI/BehaviourTree.hpp"
#include "botcraft/AI/Tasks/AllTasks.hpp"

#include "ChatCommandClient.hpp"

using namespace Botcraft;
using namespace ProtocolCraft;

ChatCommandClient::ChatCommandClient(const bool use_renderer_) : TemplatedBehaviourClient<ChatCommandClient>(use_renderer_)
{
    std::cout << "Known commands:\n";
    std::cout << "    Pathfinding to position:\n";
    std::cout << "        name goto x y z (speed)\n";
    std::cout << "    Stop what you're doing:\n";
    std::cout << "        name stop\n";
    std::cout << "    Check perimeter for spawnable blocks and save spawnable positions to file:\n";
    std::cout << "        name check_perimeter [x y z (default = player position)] radius (default = 128) [check_lighting (default = true)]\n";
    std::cout << "    Disconnect:\n";
    std::cout << "        name die\n";
    std::cout << "    Place a block:\n";
    std::cout << "        name place_block minecraft:item x y z\n";
    std::cout << "    Break a block:\n";
    std::cout << "        name dig x y z\n";
    std::cout << "    Interact (right click) a block:\n";
    std::cout << "        name interact x y z\n";
}

ChatCommandClient::~ChatCommandClient()
{
    
}

#if PROTOCOL_VERSION < 759
void ChatCommandClient::Handle(ClientboundChatPacket &msg)
{
    ManagersClient::Handle(msg);
    
    // Split the message 
    std::istringstream ss{ msg.GetMessage().GetText() };
    const std::vector<std::string> splitted({ std::istream_iterator<std::string>{ss}, std::istream_iterator<std::string>{} });

    // Process it
    ProcessChatMsg(splitted);
}
#else
void ChatCommandClient::Handle(ClientboundPlayerChatPacket& msg)
{
    ManagersClient::Handle(msg);

    // Split the message
#if PROTOCOL_VERSION == 759
    std::istringstream ss{ msg.GetSignedContent().GetText() };
#elif PROTOCOL_VERSION == 760
    std::istringstream ss{ msg.GetMessage_().GetSignedBody().GetContent().GetPlain() };
#else
    std::istringstream ss{ msg.GetBody().GetContent() };
#endif
    const std::vector<std::string> splitted({ std::istream_iterator<std::string>{ss}, std::istream_iterator<std::string>{} });

    // Process it
    ProcessChatMsg(splitted);
}

void ChatCommandClient::Handle(ClientboundSystemChatPacket& msg)
{
    ManagersClient::Handle(msg);

    // Split the message
    std::istringstream ss{ msg.GetContent().GetText() };
    const std::vector<std::string> splitted({ std::istream_iterator<std::string>{ss}, std::istream_iterator<std::string>{} });

    // Process it
    ProcessChatMsg(splitted);
}
#endif

void ChatCommandClient::ProcessChatMsg(const std::vector<std::string>& splitted_msg)
{
    if (splitted_msg.size() < 2 || splitted_msg[0] != network_manager->GetMyName())
    {
        return;
    }

    if (splitted_msg[1] == "goto")
    {
        if (splitted_msg.size() < 5)
        {
            SendChatMessage("Usage: [BotName] [goto] [x] [y] [z] [speed]");
            return;
        }
        Position target_position;
        float speed = 0.0f;
        try
        {
            target_position = Position(std::stoi(splitted_msg[2]), std::stoi(splitted_msg[3]), std::stoi(splitted_msg[4]));
            if (splitted_msg.size() > 5)
            {
                speed = std::stof(splitted_msg[5]);
            }
        }
        catch (const std::invalid_argument &)
        {
            return;
        }
        catch (const std::out_of_range &)
        {
            return;
        }

        auto tree = Builder<ChatCommandClient>("goto tree")
            .sequence()
                // Perform the pathfinding in a Selector,
                // so it exits as soon as one leaf
                // returns success
                .selector()
                    // The next three lines do exactly the same,
                    // they're only here to show the different
                    // possibilities to create a leaf. Note that
                    // only the lambda solution can use default
                    // parameters for the last bool value
                    .leaf("go to lambda", [=](ChatCommandClient& c) { return GoTo(c, target_position, 4, 1, 1, speed); })
                    .leaf("go to function", GoTo, target_position, 0, 0, 0, speed, true)
                    .leaf("go to std::bind", std::bind(GoTo, std::placeholders::_1, target_position, 0, 0, 0, speed, true))
                    // If goto fails, say something in chat
                    .leaf(Say, "Pathfinding failed :(")
                .end()
                // Switch back to empty behaviour
                .leaf([](ChatCommandClient& c) { c.SetBehaviourTree(nullptr); return Status::Success; })
            .end();

        SetBehaviourTree(tree);
    }
    else if (splitted_msg[1] == "stop")
    {
        // Stop any running behaviour
        SetBehaviourTree(nullptr);
    }
    else if (splitted_msg[1] == "check_perimeter")
    {
        float radius = 128.0f;
        Position pos = Position(
            static_cast<int>(std::floor(entity_manager->GetLocalPlayer()->GetPosition().x)),
            static_cast<int>(std::floor(entity_manager->GetLocalPlayer()->GetPosition().y)),
            static_cast<int>(std::floor(entity_manager->GetLocalPlayer()->GetPosition().z))
        );
        bool check_lighting = true;

        if (splitted_msg.size() == 3)
        {
            radius = std::stof(splitted_msg[2]);
        }
        else if (splitted_msg.size() == 4)
        {
            radius = std::stof(splitted_msg[2]);
            check_lighting = std::stoi(splitted_msg[3]);
        }
        else if (splitted_msg.size() == 6)
        {
            pos = Position(std::stoi(splitted_msg[2]), std::stoi(splitted_msg[3]), std::stoi(splitted_msg[4]));
            radius = std::stof(splitted_msg[5]);
        }
        else if (splitted_msg.size() == 7)
        {
            pos = Position(std::stoi(splitted_msg[2]), std::stoi(splitted_msg[3]), std::stoi(splitted_msg[4]));
            radius = std::stof(splitted_msg[5]);
            check_lighting = std::stoi(splitted_msg[6]);
        }
        CheckPerimeter(pos, radius, check_lighting);
    }
    else if (splitted_msg[1] == "die")
    {
        should_be_closed = true;
    }
    else if (splitted_msg[1] == "place_block")
    {
        if (splitted_msg.size() < 6)
        {
            SendChatMessage("Usage: [BotName] [place_block] [item] [x] [y] [z]");
            return;
        }
        const std::string& item = splitted_msg[2];
        Position pos;
        try
        {
            pos = Position(std::stoi(splitted_msg[3]), std::stoi(splitted_msg[4]), std::stoi(splitted_msg[5]));
        }
        catch (const std::invalid_argument&)
        {
            return;
        }
        catch (const std::out_of_range&)
        {
            return;
        }
        LOG_INFO("Asked to place a block at " << pos << " (" << item << ")");

        auto tree = Builder<ChatCommandClient>("place block")
            // shortcut for composite<Sequence<ChatCommandClient>>()
            .sequence()
                .succeeder().leaf(PlaceBlock, item, pos, PlayerDiggingFace::Up, true, true)
                // Switch back to empty behaviour
                .leaf([](ChatCommandClient& c) { c.SetBehaviourTree(nullptr); return Status::Success; })
            .end();

        SetBehaviourTree(tree);
    }
    else if (splitted_msg[1] == "dig")
    {
        if (splitted_msg.size() < 5)
        {
            SendChatMessage("Usage: [BotName] [dig] [x] [y] [z]");
            return;
        }

        Position pos;
        try
        {
            pos = Position(std::stoi(splitted_msg[2]), std::stoi(splitted_msg[3]), std::stoi(splitted_msg[4]));
        }
        catch (const std::invalid_argument&)
        {
            return;
        }
        catch (const std::out_of_range&)
        {
            return;
        }

        auto tree = Builder<ChatCommandClient>("dig")
            // shortcut for composite<Sequence<ChatCommandClient>>()
            .sequence()
                .succeeder().leaf("diggy diggy hole", Dig, pos, true, PlayerDiggingFace::Up)
                // Switch back to empty behaviour
                .leaf([](ChatCommandClient& c) { c.SetBehaviourTree(nullptr); return Status::Success; })
            .end();

        SetBehaviourTree(tree);
    }
    else if (splitted_msg[1] == "interact")
    {
        if (splitted_msg.size() < 5)
        {
            SendChatMessage("Usage: [BotName] [interact] [x] [y] [z]");
            return;
        }
        Position pos;
        try
        {
            pos = Position(std::stoi(splitted_msg[2]), std::stoi(splitted_msg[3]), std::stoi(splitted_msg[4]));
        }
        catch (const std::invalid_argument&)
        {
            return;
        }
        catch (const std::out_of_range&)
        {
            return;
        }

        auto tree = Builder<ChatCommandClient>("interact")
            // shortcut for composite<Sequence<ChatCommandClient>>()
            .sequence()
                .succeeder().sequence()
                    .leaf("go next to block", GoTo, pos, 4, 0, 1, 0.0f, true)
                    // Set interaction position in the blackboard
                    .leaf(SetBlackboardData<Position>, "InteractWithBlock.pos", pos)
                    .selector()
                        // Perform action using the data in the blackboard
                        .leaf("interact with block", InteractWithBlockBlackboard)
                        // Say something if it fails
                        .leaf(Say, "Interacting failed :(")
                    .end()
                    // Remove interaction position in the blackboard because
                    // we don't want to leave a mess (and to show how to do it)
                    .leaf(RemoveBlackboardData, "InteractWithBlock.pos")
                .end()
                // Switch back to empty behaviour
                .leaf([](ChatCommandClient& c) { c.SetBehaviourTree(nullptr); return Status::Success; })
            .end();

        SetBehaviourTree(tree);
    }
    else
    {
        return;
    }
}

void ChatCommandClient::CheckPerimeter(const Position &pos, const float radius, const bool check_lighting)
{
    std::vector<Position> found_positions;

    Position current_position;
    for (int y = static_cast<int>(-radius - 1); y < radius + 1; ++y)
    {
        current_position.y = pos.y + y;
        for (int x = static_cast<int>(-radius - 1); x < radius + 1; ++x)
        {
            current_position.x = pos.x + x;
            for (int z = static_cast<int>(-radius - 1); z < radius + 1; ++z)
            {
                current_position.z = pos.z + z;

                if (x * x + y * y + z * z > radius * radius)
                {
                    continue;
                }

                std::lock_guard<std::mutex> world_guard(world->GetMutex());

                const Block *block = world->GetBlock(current_position);

                if (!block || !block->GetBlockstate()->IsAir())
                {
                    continue;
                }

                Position adjacent_position = current_position;
                adjacent_position.y -= 1;

                const Block *adjacent_block = world->GetBlock(adjacent_position);
                
                if (!adjacent_block ||
                    adjacent_block->GetBlockstate()->IsFluid() ||
                    !adjacent_block->GetBlockstate()->IsSolid() ||
                    adjacent_block->GetBlockstate()->IsTransparent() ||
                    adjacent_block->GetBlockstate()->GetName() == "minecraft:bedrock" ||
                    adjacent_block->GetBlockstate()->GetName() == "minecraft:barrier")
                {
                    continue;
                }

                adjacent_position.y += 2;

                adjacent_block = world->GetBlock(adjacent_position);

                if (adjacent_block &&
                    (adjacent_block->GetBlockstate()->IsSolid() ||
                    adjacent_block->GetBlockstate()->IsFluid()))
                {
                    continue;
                }

                if (check_lighting && world->GetBlockLight(current_position) > 7)
                {
                    continue;
                }

                found_positions.push_back(current_position);
            }
        }
    }

    std::ofstream output_file("perimeter_check_" + std::to_string(pos.x) + "_" + std::to_string(pos.y) + "_" + std::to_string(pos.z) + "_radius_" + std::to_string(radius) + ".txt", std::ios::out);

    if (output_file.is_open())
    {
        for (int i = 0; i < found_positions.size(); ++i)
        {
            output_file << found_positions[i] << "\n";
        }

        output_file.close();
    }
}
