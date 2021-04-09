#include <sstream>
#include <fstream>

#include <botcraft/Game/World/World.hpp>
#include <botcraft/Game/World/Block.hpp>
#include <botcraft/Game/Entities/EntityManager.hpp>
#include <botcraft/Game/Entities/LocalPlayer.hpp>
#include <botcraft/Network/NetworkManager.hpp>

#include "MapCreatorBot.hpp"

using namespace Botcraft;
using namespace ProtocolCraft;

MapCreatorBot::MapCreatorBot(const std::string& map_file_, const bool use_renderer_, const bool is_afk_) : InterfaceClient(use_renderer_, is_afk_)
{
    map_file = map_file_;
}

MapCreatorBot::~MapCreatorBot()
{
    
}

void MapCreatorBot::Handle(ChatMessageClientbound &msg)
{
    BaseClient::Handle(msg);
    
    // Split the message 
    std::istringstream ss{ msg.GetJsonData().GetText() };
    const std::vector<std::string> splitted({ std::istream_iterator<std::string>{ss}, std::istream_iterator<std::string>{} });

    if (splitted.size() < 2 || splitted[0] != network_manager->GetMyName())
    {
        return;
    }

    if (splitted[1] == "start")
    {
        if (splitted.size() < 2)
        {
            Say("Usage: [BotName] [start]");
            return;
        }

        std::thread map_creation_thread(&MapCreatorBot::CreateMap, this);
        map_creation_thread.detach();
    }
    else
    {
        return;
    }
}

void MapCreatorBot::CreateMap()
{
    std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();
    const Position player_position(local_player->GetX(), local_player->GetY(), local_player->GetZ());
    Position checked_position;
    {
        std::lock_guard<std::mutex> world_guard(world->GetMutex());
        const Block* block;
        for (int x = -256; x < 256; ++x)
        {
            checked_position.x = player_position.x + x;
            for (int y = 0; y < 256; ++y)
            {
                checked_position.y = player_position.y + y;
                for (int z = -256; z < 256; ++z)
                {
                    checked_position.z = player_position.z + z;
                    block = world->GetBlock(checked_position);
                    if (block && block->GetBlockstate()->GetName() == "minecraft:chest")
                    {
                        std::cout << "Chest found in " << checked_position << std::endl;
                    }
                }
            }
        }
    }
}
