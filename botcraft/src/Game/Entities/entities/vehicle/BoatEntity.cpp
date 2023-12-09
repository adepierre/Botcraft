#include "botcraft/Game/Entities/entities/vehicle/BoatEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, BoatEntity::metadata_count> BoatEntity::metadata_names{ {
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        "data_id_hurt",
        "data_id_hurtdir",
        "data_id_damage",
#endif
        "data_id_type",
        "data_id_paddle_left",
        "data_id_paddle_right",
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        "data_id_bubble_time",
#endif
    } };

    BoatEntity::BoatEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        SetDataIdHurt(0);
        SetDataIdHurtdir(1);
        SetDataIdDamage(0.0f);
#endif
        SetDataIdType(0);
        SetDataIdPaddleLeft(false);
        SetDataIdPaddleRight(false);
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        SetDataIdBubbleTime(0);
#endif
    }

    BoatEntity::~BoatEntity()
    {

    }


    std::string BoatEntity::GetName() const
    {
        return "boat";
    }

    EntityType BoatEntity::GetType() const
    {
        return EntityType::Boat;
    }


    std::string BoatEntity::GetClassName()
    {
        return "boat";
    }

    EntityType BoatEntity::GetClassType()
    {
        return EntityType::Boat;
    }


    ProtocolCraft::Json::Value BoatEntity::Serialize() const
    {
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        ProtocolCraft::Json::Value output = Entity::Serialize();
#else
        ProtocolCraft::Json::Value output = VehicleEntity::Serialize();
#endif

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        output["metadata"]["data_id_hurt"] = GetDataIdHurt();
        output["metadata"]["data_id_hurtdir"] = GetDataIdHurtdir();
        output["metadata"]["data_id_damage"] = GetDataIdDamage();
#endif
        output["metadata"]["data_id_type"] = GetDataIdType();
        output["metadata"]["data_id_paddle_left"] = GetDataIdPaddleLeft();
        output["metadata"]["data_id_paddle_right"] = GetDataIdPaddleRight();
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        output["metadata"]["data_id_bubble_time"] = GetDataIdBubbleTime();
#endif

        return output;
    }


    void BoatEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
            Entity::SetMetadataValue(index, value);
#else
            VehicleEntity::SetMetadataValue(index, value);
#endif
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    int BoatEntity::GetDataIdHurt() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_id_hurt"));
    }

    int BoatEntity::GetDataIdHurtdir() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_id_hurtdir"));
    }

    float BoatEntity::GetDataIdDamage() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<float>(metadata.at("data_id_damage"));
    }
#endif

    int BoatEntity::GetDataIdType() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_id_type"));
    }

    bool BoatEntity::GetDataIdPaddleLeft() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_id_paddle_left"));
    }

    bool BoatEntity::GetDataIdPaddleRight() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_id_paddle_right"));
    }

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    int BoatEntity::GetDataIdBubbleTime() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_id_bubble_time"));
    }
#endif


#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    void BoatEntity::SetDataIdHurt(const int data_id_hurt)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_hurt"] = data_id_hurt;
    }

    void BoatEntity::SetDataIdHurtdir(const int data_id_hurtdir)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_hurtdir"] = data_id_hurtdir;
    }

    void BoatEntity::SetDataIdDamage(const float data_id_damage)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_damage"] = data_id_damage;
    }
#endif

    void BoatEntity::SetDataIdType(const int data_id_type)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_type"] = data_id_type;
    }

    void BoatEntity::SetDataIdPaddleLeft(const bool data_id_paddle_left)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_paddle_left"] = data_id_paddle_left;
    }

    void BoatEntity::SetDataIdPaddleRight(const bool data_id_paddle_right)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_paddle_right"] = data_id_paddle_right;
    }

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    void BoatEntity::SetDataIdBubbleTime(const int data_id_bubble_time)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_bubble_time"] = data_id_bubble_time;
    }
#endif


    double BoatEntity::GetWidthImpl() const
    {
        return 1.375;
    }

    double BoatEntity::GetHeightImpl() const
    {
        return 0.5625;
    }

}
