#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "botcraft/Game/Entities/entities/vehicle/boat/ChestBoatEntity.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
    ChestBoatEntity::ChestBoatEntity()
#else
    ChestBoatEntity::ChestBoatEntity(const EntityType type) : type(type)
#endif
    {

    }

    ChestBoatEntity::~ChestBoatEntity()
    {

    }


    std::string ChestBoatEntity::GetName() const
    {
        return "chest_boat";
    }

    EntityType ChestBoatEntity::GetType() const
    {
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        return EntityType::ChestBoat;
#else
        return type;
#endif
    }


    std::string ChestBoatEntity::GetClassName()
    {
        return "chest_boat";
    }

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
    EntityType ChestBoatEntity::GetClassType()
    {
        return EntityType::ChestBoat;
    }
#else
    bool ChestBoatEntity::IsChestBoat() const
    {
        return true;
    }
#endif

#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    ProtocolCraft::Json::Value ChestBoatEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractChestBoatEntity::Serialize();

        output["type"] = type;

        return output;
    }
#endif

    double ChestBoatEntity::GetWidthImpl() const
    {
        return 1.375;
    }

    double ChestBoatEntity::GetHeightImpl() const
    {
        return 0.5625;
    }

}
#endif
