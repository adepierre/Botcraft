#include "botcraft/Game/Entities/entities/monster/ZombieEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, ZombieEntity::metadata_count> ZombieEntity::metadata_names{ {
        "data_baby_id",
        "data_special_type_id",
#if PROTOCOL_VERSION < 405 /* < 1.14 */
        "data_are_hands_up",
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        "data_drowned_conversion_id",
#endif
    } };

    ZombieEntity::ZombieEntity()
    {
        // Initialize all metadata with default values
        SetDataBabyId(false);
        SetDataSpecialTypeId(0);
#if PROTOCOL_VERSION < 405 /* < 1.14 */
        SetDataAreHandsUp(false);
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        SetDataDrownedConversionId(false);
#endif
    }

    ZombieEntity::~ZombieEntity()
    {

    }


    std::string ZombieEntity::GetName() const
    {
        return "zombie";
    }

    EntityType ZombieEntity::GetType() const
    {
        return EntityType::Zombie;
    }


    std::string ZombieEntity::GetClassName()
    {
        return "zombie";
    }

    EntityType ZombieEntity::GetClassType()
    {
        return EntityType::Zombie;
    }


    ProtocolCraft::Json::Value ZombieEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_baby_id"] = GetDataBabyId();
        output["metadata"]["data_special_type_id"] = GetDataSpecialTypeId();
#if PROTOCOL_VERSION < 405 /* < 1.14 */
        output["metadata"]["data_are_hands_up"] = GetDataAreHandsUp();
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
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
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool ZombieEntity::GetDataBabyId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_baby_id"));
    }

    int ZombieEntity::GetDataSpecialTypeId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_special_type_id"));
    }

#if PROTOCOL_VERSION < 405 /* < 1.14 */
    bool ZombieEntity::GetDataAreHandsUp() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_are_hands_up"));
    }
#endif

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    bool ZombieEntity::GetDataDrownedConversionId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_drowned_conversion_id"));
    }
#endif


    void ZombieEntity::SetDataBabyId(const bool data_baby_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_baby_id"] = data_baby_id;
    }

    void ZombieEntity::SetDataSpecialTypeId(const int data_special_type_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_special_type_id"] = data_special_type_id;
    }

#if PROTOCOL_VERSION < 405 /* < 1.14 */
    void ZombieEntity::SetDataAreHandsUp(const bool data_are_hands_up)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_are_hands_up"] = data_are_hands_up;
    }
#endif

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    void ZombieEntity::SetDataDrownedConversionId(const bool data_drowned_conversion_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_drowned_conversion_id"] = data_drowned_conversion_id;
    }
#endif


    double ZombieEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double ZombieEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
