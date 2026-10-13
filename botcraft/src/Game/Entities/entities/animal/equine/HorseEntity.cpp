#include "botcraft/Game/Entities/entities/animal/equine/HorseEntity.hpp"

namespace Botcraft
{
    HorseEntity::HorseEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataIdTypeVariant(0);
#if PROTOCOL_VERSION < 405 /* < 1.14 */
        SetArmorType(std::optional<int>());
#endif
    }

    HorseEntity::~HorseEntity()
    {

    }


    std::string HorseEntity::GetName() const
    {
        return "horse";
    }

    EntityType HorseEntity::GetType() const
    {
        return EntityType::Horse;
    }


    std::string HorseEntity::GetClassName()
    {
        return "horse";
    }

    EntityType HorseEntity::GetClassType()
    {
        return EntityType::Horse;
    }


    ProtocolCraft::Json::Value HorseEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractHorseEntity::Serialize();

        output["metadata"]["data_id_type_variant"] = GetDataIdTypeVariant();
#if PROTOCOL_VERSION < 405 /* < 1.14 */
        output["metadata"]["armor_type"] = GetArmorType() ? ProtocolCraft::Json::Value(GetArmorType().value()) : ProtocolCraft::Json::Value();
#endif

        return output;
    }


    int HorseEntity::GetDataIdTypeVariant() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_type_variant"));
    }

#if PROTOCOL_VERSION < 405 /* < 1.14 */
    std::optional<int> HorseEntity::GetArmorType() const
    {
        return GetMetadata<std::optional<int>>(BOTCRAFT_ENTITY_METADATA_INDEX("armor_type"));
    }
#endif


    void HorseEntity::SetDataIdTypeVariant(const int data_id_type_variant)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_type_variant"), data_id_type_variant);
    }

#if PROTOCOL_VERSION < 405 /* < 1.14 */
    void HorseEntity::SetArmorType(const std::optional<int>& armor_type)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("armor_type"), armor_type);
    }
#endif


    double HorseEntity::GetWidthImpl() const
    {
        return 1.3964844;
    }

    double HorseEntity::GetHeightImpl() const
    {
        return 1.6;
    }

}
