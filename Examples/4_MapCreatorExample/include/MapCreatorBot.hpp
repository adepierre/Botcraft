#pragma once

#include <botcraft/Game/Vector3.hpp>
#include <botcraft/Game/InterfaceClient.hpp>
#include <botcraft/Game/World/Blockstate.hpp>

#include <random>
#include <set>
#include <map>

class MapCreatorBot : public Botcraft::InterfaceClient
{
public:
    MapCreatorBot(const std::string& map_file_, const Botcraft::Position& offset_, const bool use_renderer_);
    ~MapCreatorBot();

protected:
    virtual void Handle(ProtocolCraft::ClientboundChatPacket &msg) override;

private:
    void LoadNBTFile(const std::string& path);

    // Get the positions of all chests in a 2*max_search_dist blocks
    // cube centered around the player
    // max_search_dist: max distance to search, in each direction
    // returns: a vector with all the found positions
    const std::vector<Botcraft::Position> GetAllChestsAround(const Botcraft::Position& max_search_dist) const;

    const bool GetSomeFood(const std::string& item_name);
    const bool GetSomeBlocks(const std::string& food_name);
    const std::set<std::string> GetBlocksAvailableInInventory() const;


    void CreateMap();

private:
    std::vector<std::vector<std::vector<int> > > target;
    std::map<int, std::string> palette;
    Botcraft::Position offset;

    std::mt19937 random_engine;

};