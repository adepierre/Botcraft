#include "botcraft/Game/Entities/entities/animal/equine/AbstractChestedHorseEntity.hpp"

namespace Botcraft
{
    AbstractChestedHorseEntity::AbstractChestedHorseEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataIdChest(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.175) });
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        attributes.insert({ EntityAttribute::Type::HorseJumpStrength, EntityAttribute(EntityAttribute::Type::HorseJumpStrength, 0.5) });
#else
        attributes.insert({ EntityAttribute::Type::JumpStrength, EntityAttribute(EntityAttribute::Type::JumpStrength, 0.5) });
#endif
    }

    AbstractChestedHorseEntity::~AbstractChestedHorseEntity()
    {

    }

    bool AbstractChestedHorseEntity::IsAbstractChestedHorse() const
    {
        return true;
    }


    ProtocolCraft::Json::Value AbstractChestedHorseEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractHorseEntity::Serialize();

        output["metadata"]["data_id_chest"] = GetDataIdChest();

        return output;
    }


    bool AbstractChestedHorseEntity::GetDataIdChest() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_chest"));
    }


    void AbstractChestedHorseEntity::SetDataIdChest(const bool data_id_chest)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_chest"), data_id_chest);
    }

}
