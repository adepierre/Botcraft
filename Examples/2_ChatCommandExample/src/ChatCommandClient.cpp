#include <sstream>
#include <fstream>

#include <botcraft/Game/World/World.hpp>
#include <botcraft/Game/World/Block.hpp>
#include <botcraft/Game/Entities/EntityManager.hpp>
#include <botcraft/Game/Entities/LocalPlayer.hpp>
#include <botcraft/Network/NetworkManager.hpp>

#include "ChatCommandClient.hpp"

using namespace Botcraft;
using namespace ProtocolCraft;

ChatCommandClient::ChatCommandClient(const bool use_renderer_, const bool is_afk_) : InterfaceClient(use_renderer_, is_afk_)
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
    std::cout << "    Place a block:\n";
    std::cout << "        name place_block minecraft:item x y z\n";
    std::cout << "    Interact (right click) a block:\n";
    std::cout << "        name interact x y z\n";
}

ChatCommandClient::~ChatCommandClient()
{
    
}

void ChatCommandClient::Handle(ClientboundChatPacket &msg)
{
    BaseClient::Handle(msg);
    
    // Split the message 
    std::istringstream ss{ msg.GetMessage().GetText() };
    const std::vector<std::string> splitted({ std::istream_iterator<std::string>{ss}, std::istream_iterator<std::string>{} });

    if (splitted.size() < 2 || splitted[0] != network_manager->GetMyName())
    {
        return;
    }

    if (splitted[1] == "goto")
    {
        if (splitted.size() < 5)
        {
            Say("Usage: goto <x> <y> <z>");
            return;
        }
        Position target_position;
        float speed = 4.317f;
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
        std::thread t(&ChatCommandClient::GoTo, this, target_position, false, 0, speed);
        t.detach();
    }
    else if (splitted[1] == "stop")
    {
        StopPathFinding();
    }
    else if (splitted[1] == "check_perimeter")
    {
        float radius = 128.0f;
        Position pos = Position(entity_manager->GetLocalPlayer()->GetPosition().x, entity_manager->GetLocalPlayer()->GetPosition().y, entity_manager->GetLocalPlayer()->GetPosition().z);
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
    else if (splitted[1] == "say")
    {
		if (splitted.size() < 3)
		{
            Say("Usage: say <message>");
            return;
		}
		std::string saymsg = "";
		for (auto it = splitted.begin()+2; it != splitted.end(); it++)
		{
			saymsg += *it + " ";
		}
		Say(saymsg);
    }
    else if (splitted[1] == "place_block")
    {
        if (splitted.size() < 6)
        {
            Say("Usage: place_block <item> <x> <y> <z>");
            return;
        }
        const std::string item = splitted[2];
        Position pos;
        try
        {
            pos = Position(std::stoi(splitted[3]), std::stoi(splitted[4]), std::stoi(splitted[5]));
        }
        catch (const std::invalid_argument& e)
        {
            return;
        }
        catch (const std::out_of_range& e)
        {
            return;
        }

        PlaceBlock(item, pos, PlayerDiggingFace::Top, false);
    }
    else if (splitted[1] == "interact")
    {
        if (splitted.size() < 5)
        {
            Say("Usage: interact <x> <y> <z>");
            return;
        }
        Position pos;
        try
        {
            pos = Position(std::stoi(splitted[2]), std::stoi(splitted[3]), std::stoi(splitted[4]));
        }
        catch (const std::invalid_argument& e)
        {
            return;
        }
        catch (const std::out_of_range& e)
        {
            return;
        }

        InteractWithBlock(pos, PlayerDiggingFace::Top, true);
    }
    else if (splitted[1] == "killaura")
    {
		if (splitted.size() < 3)
		{
            Say("Usage: killaura <action> [...]");
            return;
		}
		if (splitted[2] == "block")
		{
			if (splitted.size() < 6)
	        {
	            Say("Usage: killaura block <x> <y> <z>");
	            return;
	        }
	        Position pos;
	        try
	        {
	            pos = Position(std::stoi(splitted[3]), std::stoi(splitted[4]), std::stoi(splitted[5]));
	        }
	        catch (const std::invalid_argument& e)
	        {
	            return;
	        }
	        catch (const std::out_of_range& e)
	        {
	            return;
	        }

	        // Launch the command on a new thread
	        std::thread t(&ChatCommandClient::KillAuraBlock, this, pos, 3000);
	        t.detach();
		}
		else if (splitted[2] == "stop")
		{
			StopKillAura();
			std::cout << "KillAura stopped." << std::endl;
		}
		else
		{
			Say("Available killaura actions: block, stop");
			return;
		}
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
