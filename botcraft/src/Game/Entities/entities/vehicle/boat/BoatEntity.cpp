#include "botcraft/Game/Entities/entities/vehicle/boat/BoatEntity.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
    BoatEntity::BoatEntity()
#else
    BoatEntity::BoatEntity(const EntityType type) : type(type)
#endif
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        SetDataIdHurt(0);
        SetDataIdHurtdir(1);
        SetDataIdDamage(0.0f);
#endif
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SetDataIdType(0);
        SetDataIdPaddleLeft(false);
        SetDataIdPaddleRight(false);
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        SetDataIdBubbleTime(0);
#endif
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
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        return EntityType::Boat;
#else
        return type;
#endif
    }


    std::string BoatEntity::GetClassName()
    {
        return "boat";
    }

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
    EntityType BoatEntity::GetClassType()
    {
        return EntityType::Boat;
    }
#else
    bool BoatEntity::IsBoat() const
    {
        return true;
    }
#endif


    ProtocolCraft::Json::Value BoatEntity::Serialize() const
    {
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        ProtocolCraft::Json::Value output = Entity::Serialize();
#elif PROTOCOL_VERSION < 768 /* < 1.21.2 */
        ProtocolCraft::Json::Value output = VehicleEntity::Serialize();
#else
        ProtocolCraft::Json::Value output = AbstractBoatEntity::Serialize();
#endif

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
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
#else
        output["type"] = type;
#endif

        return output;
    }


#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    int BoatEntity::GetDataIdHurt() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_hurt"));
    }

    int BoatEntity::GetDataIdHurtdir() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_hurtdir"));
    }

    float BoatEntity::GetDataIdDamage() const
    {
        return GetMetadata<float>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_damage"));
    }
#endif

    int BoatEntity::GetDataIdType() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_type"));
    }

    bool BoatEntity::GetDataIdPaddleLeft() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_paddle_left"));
    }

    bool BoatEntity::GetDataIdPaddleRight() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_paddle_right"));
    }

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    int BoatEntity::GetDataIdBubbleTime() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_bubble_time"));
    }
#endif


#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    void BoatEntity::SetDataIdHurt(const int data_id_hurt)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_hurt"), data_id_hurt);
    }

    void BoatEntity::SetDataIdHurtdir(const int data_id_hurtdir)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_hurtdir"), data_id_hurtdir);
    }

    void BoatEntity::SetDataIdDamage(const float data_id_damage)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_damage"), data_id_damage);
    }
#endif

    void BoatEntity::SetDataIdType(const int data_id_type)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_type"), data_id_type);
    }

    void BoatEntity::SetDataIdPaddleLeft(const bool data_id_paddle_left)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_paddle_left"), data_id_paddle_left);
    }

    void BoatEntity::SetDataIdPaddleRight(const bool data_id_paddle_right)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_paddle_right"), data_id_paddle_right);
    }

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    void BoatEntity::SetDataIdBubbleTime(const int data_id_bubble_time)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_bubble_time"), data_id_bubble_time);
    }
#endif
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
