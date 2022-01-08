#include "botcraft/Game/Entities/entities/monster/ZombieEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, ZombieEntity::metadata_count> ZombieEntity::metadata_names{ {
        "data_baby_id",
        "data_special_type_id",
#if PROTOCOL_VERSION < 405
        "data_are_hands_up",
#endif
#if PROTOCOL_VERSION > 340
        "data_drowned_conversion_id",
#endif
    } };

    ZombieEntity::ZombieEntity()
    {
        // Initialize all metadata with default values
        SetDataBabyId(false);
        SetDataSpecialTypeId(0);
#if PROTOCOL_VERSION < 405
        SetDataAreHandsUp(false);
#endif
#if PROTOCOL_VERSION > 340
        SetDataDrownedConversionId(false);
#endif
    }

    ZombieEntity::~ZombieEntity()
    {

    }


    std::string ZombieEntity::GetName() const
    {
        return "Zombie";
    }

    EntityType ZombieEntity::GetType() const
    {
        return EntityType::Zombie;
    }

    AABB ZombieEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double ZombieEntity::GetWidth() const
    {
        return 0.6;
    }

    double ZombieEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string ZombieEntity::GetClassName()
    {
        return "Zombie";
    }

    EntityType ZombieEntity::GetClassType()
    {
        return EntityType::Zombie;
    }


    nlohmann::json ZombieEntity::Serialize() const
    {
        nlohmann::json output = MonsterEntity::Serialize();

        output["metadata"]["data_baby_id"] = GetDataBabyId();
        output["metadata"]["data_special_type_id"] = GetDataSpecialTypeId();
#if PROTOCOL_VERSION < 405
        output["metadata"]["data_are_hands_up"] = GetDataAreHandsUp();
#endif
#if PROTOCOL_VERSION > 340
        output["metadata"]["data_drowned_conversion_id"] = GetDataDrownedConversionId();
#endif

        return output;
    }


    void ZombieEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MonsterEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool ZombieEntity::GetDataBabyId() const
    {
        return std::any_cast<bool>(metadata.at("data_baby_id"));
    }

    int ZombieEntity::GetDataSpecialTypeId() const
    {
        return std::any_cast<int>(metadata.at("data_special_type_id"));
    }

#if PROTOCOL_VERSION < 405
    bool ZombieEntity::GetDataAreHandsUp() const
    {
        return std::any_cast<bool>(metadata.at("data_are_hands_up"));
    }
#endif

#if PROTOCOL_VERSION > 340
    bool ZombieEntity::GetDataDrownedConversionId() const
    {
        return std::any_cast<bool>(metadata.at("data_drowned_conversion_id"));
    }
#endif


    void ZombieEntity::SetDataBabyId(const bool data_baby_id)
    {
        metadata["data_baby_id"] = data_baby_id;
    }

    void ZombieEntity::SetDataSpecialTypeId(const int data_special_type_id)
    {
        metadata["data_special_type_id"] = data_special_type_id;
    }

#if PROTOCOL_VERSION < 405
    void ZombieEntity::SetDataAreHandsUp(const bool data_are_hands_up)
    {
        metadata["data_are_hands_up"] = data_are_hands_up;
    }
#endif

#if PROTOCOL_VERSION > 340
    void ZombieEntity::SetDataDrownedConversionId(const bool data_drowned_conversion_id)
    {
        metadata["data_drowned_conversion_id"] = data_drowned_conversion_id;
    }
#endif

}
