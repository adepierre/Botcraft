#pragma once

#include <botcraft/Game/Vector3.hpp>
#include <botcraft/Game/InterfaceClient.hpp>

#include <random>

class MapCreatorBot : public Botcraft::InterfaceClient
{
public:
    MapCreatorBot(const std::string& map_file_, const bool use_renderer_, const bool is_afk_);
    ~MapCreatorBot();

protected:
    virtual void Handle(ProtocolCraft::ClientboundChatPacket &msg) override;

private:
    // Get the positions of all chests in a 2*max_search_dist blocks
    // cube centered around the player
    // max_search_dist: max distance to search, in each direction
    // returns: a vector with all the found positions
    const std::vector<Botcraft::Position> GetAllChestsAround(const Botcraft::Position& max_search_dist) const;

    const bool OpenChest(const Botcraft::Position& pos);
    const bool GetSomeFood(const std::string& item_name);


    void CreateMap();

private:
    std::string map_file;

    std::mt19937 random_engine;

};