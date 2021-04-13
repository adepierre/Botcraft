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

void MapCreatorBot::Handle(ClientboundChatPacket &msg)
{
    BaseClient::Handle(msg);
    
    // Split the message 
    std::istringstream ss{ msg.GetMessage().GetText() };
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

const std::vector<Position> MapCreatorBot::GetAllChestsAround(const Position& max_search_dist) const
{
    std::vector<Position> output;

    std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();

    local_player->GetMutex().lock();
    const Position player_position(local_player->GetX(), local_player->GetY(), local_player->GetZ());
    local_player->GetMutex().unlock();

    Position checked_position;
    {
        std::lock_guard<std::mutex> world_guard(world->GetMutex());
        const Block* block;
        for (int x = -max_search_dist.x; x < max_search_dist.x; ++x)
        {
            checked_position.x = player_position.x + x;
            for (int y = -max_search_dist.y; y < max_search_dist.y; ++y)
            {
                checked_position.y = player_position.y + y;
                for (int z = -max_search_dist.z; z < max_search_dist.z; ++z)
                {
                    checked_position.z = player_position.z + z;
                    block = world->GetBlock(checked_position);
                    if (block && block->GetBlockstate()->GetName() == "minecraft:chest")
                    {
                        output.push_back(checked_position);
                    }
                }
            }
        }
    }

    return output;
}

void MapCreatorBot::CreateMap()
{
    std::vector<Position> chests = GetAllChestsAround(Position(128, 50, 128));
    for (int i = 0; i < chests.size(); ++i)
    {
        if (GoTo(chests[i], true))
        {
            break;
        }
    }

}
