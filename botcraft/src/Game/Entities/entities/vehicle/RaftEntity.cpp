#include "botcraft/Game/Entities/entities/vehicle/RaftEntity.hpp"


namespace Botcraft
{
    RaftEntity::RaftEntity(const EntityType type) : type(type)
    {

    }

    RaftEntity::~RaftEntity()
    {

    }


    std::string RaftEntity::GetName() const
    {
        return "raft";
    }

    EntityType RaftEntity::GetType() const
    {
        return type;
    }


    std::string RaftEntity::GetClassName()
    {
        return "raft";
    }

    bool RaftEntity::IsRaft() const
    {
        return true;
    }

    ProtocolCraft::Json::Value RaftEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractBoatEntity::Serialize();

        output["type"] = type;

        return output;
    }

    double RaftEntity::GetWidthImpl() const
    {
        return 1.375;
    }

    double RaftEntity::GetHeightImpl() const
    {
        return 0.5625;
    }

}
