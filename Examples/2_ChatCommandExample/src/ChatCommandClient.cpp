#include <sstream>
#include <fstream>

#include <botcraft/Game/world/World.hpp>
#include <botcraft/Game/World/Block.hpp>

#include "ChatCommandClient.hpp"

using namespace Botcraft;

ChatCommandClient::ChatCommandClient(const std::vector<int> &printed_packets_) : 
    InterfaceClient(printed_packets_)
{
    std::cout << "Known commands:\n";
    std::cout << "    Pathfinding to position:\n";
    std::cout << "        name goto x y z\n";
    std::cout << "    Stop current pathfinding:\n";
    std::cout << "        name stop\n";
    std::cout << "    Check perimeter for spawnable blocks and save spawnable positions to file:\n";
    std::cout << "        name check_perimeter [x y z (default = player position)] radius (default = 128) [check_lighting (default = true)]\n";
    std::cout << "    Disconnect:\n";
    std::cout << "        name die\n";
}

ChatCommandClient::~ChatCommandClient()
{
    
}

void ChatCommandClient::Handle(ChatMessageClientbound &msg)
{
    BaseClient::Handle(msg);
    
    // Split the message 
    std::istringstream ss{ msg.GetJsonData().GetText() };
    const std::vector<std::string> splitted({ std::istream_iterator<std::string>{ss}, std::istream_iterator<std::string>{} });

    if (splitted.size() < 2 || splitted[0] != name)
    {
        return;
    }

    if (splitted[1] == "goto")
    {
        if (splitted.size() < 5)
        {
            return;
        }
        Position target_position;
        float speed = 4.0f;
        try
        {
            target_position = Position(std::stoi(splitted[2]), std::stoi(splitted[3]), std::stoi(splitted[4]));
            if (splitted.size() > 5)
            {
                speed = std::stof(splitted[5]);
            }
        }
        catch (const std::invalid_argument &e)
        {
            return;
        }
        catch (const std::out_of_range &e)
        {
            return;
        }

        // Launch the command on a new thread
        std::thread t(&ChatCommandClient::GoTo, this, target_position, speed);
        t.detach();
    }
    else if (splitted[1] == "stop")
    {
        StopPathFinding();
    }
    else if (splitted[1] == "check_perimeter")
    {
        float radius = 128.0f;
        Position pos = Position(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
        bool check_lighting = true;

        if (splitted.size() == 3)
        {
            radius = std::stof(splitted[2]);
        }
        else if (splitted.size() == 4)
        {
            radius = std::stof(splitted[2]);
            check_lighting = std::stoi(splitted[3]);
        }
        else if (splitted.size() == 6)
        {
            pos = Position(std::stoi(splitted[2]), std::stoi(splitted[3]), std::stoi(splitted[4]));
            radius = std::stof(splitted[5]);
        }
        else if (splitted.size() == 7)
        {
            pos = Position(std::stoi(splitted[2]), std::stoi(splitted[3]), std::stoi(splitted[4]));
            radius = std::stof(splitted[5]);
            check_lighting = std::stoi(splitted[6]);
        }
        CheckPerimeter(pos, radius, check_lighting);
    }
    else if (splitted[1] == "die")
    {
        should_be_closed = true;
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
    for (int y = -radius - 1; y < radius + 1; ++y)
    {
        current_position.y = pos.y + y;
        for (int x = -radius - 1; x < radius + 1; ++x)
        {
            current_position.x = pos.x + x;
            for (int z = -radius - 1; z < radius + 1; ++z)
            {
                current_position.z = pos.z + z;

                if (x * x + y * y + z * z > radius * radius)
                {
                    continue;
                }

                std::lock_guard<std::mutex> world_guard(world_mutex);

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