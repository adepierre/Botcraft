#pragma once

#include <botcraft/Game/Vector3.hpp>
#include <botcraft/Game/InterfaceClient.hpp>

class MapCreatorBot : public Botcraft::InterfaceClient
{
public:
    MapCreatorBot(const std::string& map_file_, const bool use_renderer_, const bool is_afk_);
    ~MapCreatorBot();

protected:
    virtual void Handle(ProtocolCraft::ChatMessageClientbound &msg) override;

private:
    void CreateMap();

private:
    std::string map_file;
};