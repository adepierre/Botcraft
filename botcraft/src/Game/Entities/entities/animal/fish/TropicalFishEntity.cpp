#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "botcraft/Game/Entities/entities/animal/fish/TropicalFishEntity.hpp"

namespace Botcraft
{
    TropicalFishEntity::TropicalFishEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataIdTypeVariant(0);
    }

    TropicalFishEntity::~TropicalFishEntity()
    {

    }


    std::string TropicalFishEntity::GetName() const
    {
        return "tropical_fish";
    }

    EntityType TropicalFishEntity::GetType() const
    {
        return EntityType::TropicalFish;
    }


    std::string TropicalFishEntity::GetClassName()
    {
        return "tropical_fish";
    }

    EntityType TropicalFishEntity::GetClassType()
    {
        return EntityType::TropicalFish;
    }


    ProtocolCraft::Json::Value TropicalFishEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractSchoolingFishEntity::Serialize();

        output["metadata"]["data_id_type_variant"] = GetDataIdTypeVariant();

        return output;
    }


    int TropicalFishEntity::GetDataIdTypeVariant() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_type_variant"));
    }


    void TropicalFishEntity::SetDataIdTypeVariant(const int data_id_type_variant)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_type_variant"), data_id_type_variant);
    }


    double TropicalFishEntity::GetWidthImpl() const
    {
        return 0.5;
    }

    double TropicalFishEntity::GetHeightImpl() const
    {
        return 0.4;
    }

}
#endif
