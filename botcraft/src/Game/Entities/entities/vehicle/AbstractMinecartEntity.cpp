#include "botcraft/Game/Entities/entities/vehicle/AbstractMinecartEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, AbstractMinecartEntity::metadata_count> AbstractMinecartEntity::metadata_names{ {
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        "data_id_hurt",
        "data_id_hurtdir",
        "data_id_damage",
#endif
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        "data_id_display_block",
#else
        "data_id_custom_display_block",
#endif
        "data_id_display_offset",
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        "data_id_custom_display",
#endif
    } };

    AbstractMinecartEntity::AbstractMinecartEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        SetDataIdHurt(0);
        SetDataIdHurtdir(1);
        SetDataIdDamage(0.0f);
#endif
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        SetDataIdDisplayBlock(0);
#else
        SetDataIdCustomDisplayBlock(0);
#endif
        SetDataIdDisplayOffset(6);
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        SetDataIdCustomDisplay(false);
#endif
    }

    AbstractMinecartEntity::~AbstractMinecartEntity()
    {

    }

    bool AbstractMinecartEntity::IsAbstractMinecart() const
    {
        return true;
    }


    ProtocolCraft::Json::Value AbstractMinecartEntity::Serialize() const
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
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        output["metadata"]["data_id_display_block"] = GetDataIdDisplayBlock();
#else
        output["metadata"]["data_id_custom_display_block"] = GetDataIdCustomDisplayBlock();
#endif
        output["metadata"]["data_id_display_offset"] = GetDataIdDisplayOffset();
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        output["metadata"]["data_id_custom_display"] = GetDataIdCustomDisplay();
#endif

        return output;
    }


    void AbstractMinecartEntity::SetMetadataValue(const int index, const std::any& value)
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
    int AbstractMinecartEntity::GetDataIdHurt() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_id_hurt"));
    }

    int AbstractMinecartEntity::GetDataIdHurtdir() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_id_hurtdir"));
    }

    float AbstractMinecartEntity::GetDataIdDamage() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<float>(metadata.at("data_id_damage"));
    }
#endif

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    int AbstractMinecartEntity::GetDataIdDisplayBlock() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_id_display_block"));
    }
#else
    int AbstractMinecartEntity::GetDataIdCustomDisplayBlock() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_id_custom_display_block"));
    }
#endif

    int AbstractMinecartEntity::GetDataIdDisplayOffset() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_id_display_offset"));
    }

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    bool AbstractMinecartEntity::GetDataIdCustomDisplay() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_id_custom_display"));
    }
#endif


#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    void AbstractMinecartEntity::SetDataIdHurt(const int data_id_hurt)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_hurt"] = data_id_hurt;
    }

    void AbstractMinecartEntity::SetDataIdHurtdir(const int data_id_hurtdir)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_hurtdir"] = data_id_hurtdir;
    }

    void AbstractMinecartEntity::SetDataIdDamage(const float data_id_damage)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_damage"] = data_id_damage;
    }
#endif

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    void AbstractMinecartEntity::SetDataIdDisplayBlock(const int data_id_display_block)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_display_block"] = data_id_display_block;
    }
#else
    void AbstractMinecartEntity::SetDataIdCustomDisplayBlock(const int data_id_custom_display_block)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_custom_display_block"] = data_id_custom_display_block;
    }
#endif

    void AbstractMinecartEntity::SetDataIdDisplayOffset(const int data_id_display_offset)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_display_offset"] = data_id_display_offset;
    }

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    void AbstractMinecartEntity::SetDataIdCustomDisplay(const bool data_id_custom_display)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_custom_display"] = data_id_custom_display;
    }
#endif

}
