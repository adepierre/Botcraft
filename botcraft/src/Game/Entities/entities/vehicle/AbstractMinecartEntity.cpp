#include "botcraft/Game/Entities/entities/vehicle/AbstractMinecartEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, AbstractMinecartEntity::metadata_count> AbstractMinecartEntity::metadata_names{ {
        "data_id_hurt",
        "data_id_hurtdir",
        "data_id_damage",
        "data_id_display_block",
        "data_id_display_offset",
        "data_id_custom_display",
    } };

    AbstractMinecartEntity::AbstractMinecartEntity()
    {
        // Initialize all metadata with default values
        SetDataIdHurt(0);
        SetDataIdHurtdir(1);
        SetDataIdDamage(0.0f);
        SetDataIdDisplayBlock(0);
        SetDataIdDisplayOffset(6);
        SetDataIdCustomDisplay(false);
    }

    AbstractMinecartEntity::~AbstractMinecartEntity()
    {

    }

    bool AbstractMinecartEntity::IsAbstractMinecart() const
    {
        return true;
    }


    nlohmann::json AbstractMinecartEntity::Serialize() const
    {
        nlohmann::json output = Entity::Serialize();

        output["metadata"]["data_id_hurt"] = GetDataIdHurt();
        output["metadata"]["data_id_hurtdir"] = GetDataIdHurtdir();
        output["metadata"]["data_id_damage"] = GetDataIdDamage();
        output["metadata"]["data_id_display_block"] = GetDataIdDisplayBlock();
        output["metadata"]["data_id_display_offset"] = GetDataIdDisplayOffset();
        output["metadata"]["data_id_custom_display"] = GetDataIdCustomDisplay();

        return output;
    }


    void AbstractMinecartEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            Entity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int AbstractMinecartEntity::GetDataIdHurt() const
    {
        return std::any_cast<int>(metadata.at("data_id_hurt"));
    }

    int AbstractMinecartEntity::GetDataIdHurtdir() const
    {
        return std::any_cast<int>(metadata.at("data_id_hurtdir"));
    }

    float AbstractMinecartEntity::GetDataIdDamage() const
    {
        return std::any_cast<float>(metadata.at("data_id_damage"));
    }

    int AbstractMinecartEntity::GetDataIdDisplayBlock() const
    {
        return std::any_cast<int>(metadata.at("data_id_display_block"));
    }

    int AbstractMinecartEntity::GetDataIdDisplayOffset() const
    {
        return std::any_cast<int>(metadata.at("data_id_display_offset"));
    }

    bool AbstractMinecartEntity::GetDataIdCustomDisplay() const
    {
        return std::any_cast<bool>(metadata.at("data_id_custom_display"));
    }


    void AbstractMinecartEntity::SetDataIdHurt(const int data_id_hurt)
    {
        metadata["data_id_hurt"] = data_id_hurt;
    }

    void AbstractMinecartEntity::SetDataIdHurtdir(const int data_id_hurtdir)
    {
        metadata["data_id_hurtdir"] = data_id_hurtdir;
    }

    void AbstractMinecartEntity::SetDataIdDamage(const float data_id_damage)
    {
        metadata["data_id_damage"] = data_id_damage;
    }

    void AbstractMinecartEntity::SetDataIdDisplayBlock(const int data_id_display_block)
    {
        metadata["data_id_display_block"] = data_id_display_block;
    }

    void AbstractMinecartEntity::SetDataIdDisplayOffset(const int data_id_display_offset)
    {
        metadata["data_id_display_offset"] = data_id_display_offset;
    }

    void AbstractMinecartEntity::SetDataIdCustomDisplay(const bool data_id_custom_display)
    {
        metadata["data_id_custom_display"] = data_id_custom_display;
    }

}
