#include "botcraft/Game/Entities/entities/monster/ShulkerEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, ShulkerEntity::metadata_count> ShulkerEntity::metadata_names{ {
        "data_attach_face_id",
#if PROTOCOL_VERSION < 755
        "data_attach_pos_id",
#endif
        "data_peek_id",
        "data_color_id",
    } };

    ShulkerEntity::ShulkerEntity()
    {
        // Initialize all metadata with default values
        SetDataAttachFaceId(Direction::Down);
#if PROTOCOL_VERSION < 755
        SetDataAttachPosId(std::optional<Position>());
#endif
        SetDataPeekId(0);
        SetDataColorId(16);
    }

    ShulkerEntity::~ShulkerEntity()
    {

    }


    std::string ShulkerEntity::GetName() const
    {
        return "Shulker";
    }

    EntityType ShulkerEntity::GetType() const
    {
        return EntityType::Shulker;
    }

    AABB ShulkerEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double ShulkerEntity::GetWidth() const
    {
        return 1.0;
    }

    double ShulkerEntity::GetHeight() const
    {
        return 1.0;
    }


    std::string ShulkerEntity::GetClassName()
    {
        return "Shulker";
    }

    EntityType ShulkerEntity::GetClassType()
    {
        return EntityType::Shulker;
    }


    nlohmann::json ShulkerEntity::Serialize() const
    {
        nlohmann::json output = AbstractGolemEntity::Serialize();

        output["data_attach_face_id"] = static_cast<int>(GetDataAttachFaceId());
#if PROTOCOL_VERSION < 755
        output["data_attach_pos_id"] = GetDataAttachPosId() ? GetDataAttachPosId().value().Serialize() : nlohmann::json();
#endif
        output["data_peek_id"] = GetDataPeekId();
        output["data_color_id"] = GetDataColorId();

        return output;
    }


    void ShulkerEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractGolemEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    Direction ShulkerEntity::GetDataAttachFaceId() const
    {
        return std::any_cast<Direction>(metadata.at("data_attach_face_id"));
    }

#if PROTOCOL_VERSION < 755
    const std::optional<Position>& ShulkerEntity::GetDataAttachPosId() const
    {
        return std::any_cast<const std::optional<Position>&>(metadata.at("data_attach_pos_id"));
    }
#endif

    char ShulkerEntity::GetDataPeekId() const
    {
        return std::any_cast<char>(metadata.at("data_peek_id"));
    }

    char ShulkerEntity::GetDataColorId() const
    {
        return std::any_cast<char>(metadata.at("data_color_id"));
    }


    void ShulkerEntity::SetDataAttachFaceId(const Direction data_attach_face_id)
    {
        metadata["data_attach_face_id"] = data_attach_face_id;
    }

#if PROTOCOL_VERSION < 755
    void ShulkerEntity::SetDataAttachPosId(const std::optional<Position>& data_attach_pos_id)
    {
        metadata["data_attach_pos_id"] = data_attach_pos_id;
    }
#endif

    void ShulkerEntity::SetDataPeekId(const char data_peek_id)
    {
        metadata["data_peek_id"] = data_peek_id;
    }

    void ShulkerEntity::SetDataColorId(const char data_color_id)
    {
        metadata["data_color_id"] = data_color_id;
    }

}
