#include "botcraft/Game/Entities/entities/monster/WitchEntity.hpp"

namespace Botcraft
{
    WitchEntity::WitchEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataUsingItem(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 26.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.25) });
    }

    WitchEntity::~WitchEntity()
    {

    }


    std::string WitchEntity::GetName() const
    {
        return "witch";
    }

    EntityType WitchEntity::GetType() const
    {
        return EntityType::Witch;
    }


    std::string WitchEntity::GetClassName()
    {
        return "witch";
    }

    EntityType WitchEntity::GetClassType()
    {
        return EntityType::Witch;
    }


    ProtocolCraft::Json::Value WitchEntity::Serialize() const
    {
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        ProtocolCraft::Json::Value output = RaiderEntity::Serialize();
#else
        ProtocolCraft::Json::Value output = MobEntity::Serialize();
#endif

        output["metadata"]["data_using_item"] = GetDataUsingItem();

        return output;
    }


    bool WitchEntity::GetDataUsingItem() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_using_item"));
    }


    void WitchEntity::SetDataUsingItem(const bool data_using_item)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_using_item"), data_using_item);
    }


    double WitchEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double WitchEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
