#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "botcraft/Game/Entities/entities/vehicle/boat/ChestRaftEntity.hpp"


namespace Botcraft
{
    ChestRaftEntity::ChestRaftEntity(const EntityType type) : type(type)
    {

    }

    ChestRaftEntity::~ChestRaftEntity()
    {

    }


    std::string ChestRaftEntity::GetName() const
    {
        return "chest_raft";
    }

    EntityType ChestRaftEntity::GetType() const
    {
        return type;
    }


    std::string ChestRaftEntity::GetClassName()
    {
        return "chest_raft";
    }

    bool ChestRaftEntity::IsChestRaft() const
    {
        return true;
    }

    ProtocolCraft::Json::Value ChestRaftEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractChestBoatEntity::Serialize();

        output["type"] = type;

        return output;
    }


    double ChestRaftEntity::GetWidthImpl() const
    {
        return 1.375;
    }

    double ChestRaftEntity::GetHeightImpl() const
    {
        return 0.5625;
    }

}
#endif
