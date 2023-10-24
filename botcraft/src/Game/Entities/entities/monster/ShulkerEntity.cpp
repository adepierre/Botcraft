#include "botcraft/Game/Entities/entities/monster/ShulkerEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, ShulkerEntity::metadata_count> ShulkerEntity::metadata_names{ {
        "data_attach_face_id",
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        "data_attach_pos_id",
#endif
        "data_peek_id",
        "data_color_id",
    } };

    ShulkerEntity::ShulkerEntity()
    {
        // Initialize all metadata with default values
        SetDataAttachFaceId(Direction::Down);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
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
        return "shulker";
    }

    EntityType ShulkerEntity::GetType() const
    {
        return EntityType::Shulker;
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
        return "shulker";
    }

    EntityType ShulkerEntity::GetClassType()
    {
        return EntityType::Shulker;
    }


    ProtocolCraft::Json::Value ShulkerEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractGolemEntity::Serialize();

        output["metadata"]["data_attach_face_id"] = static_cast<int>(GetDataAttachFaceId());
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        output["metadata"]["data_attach_pos_id"] = GetDataAttachPosId() ? GetDataAttachPosId().value().Serialize() : ProtocolCraft::Json::Value();
#endif
        output["metadata"]["data_peek_id"] = GetDataPeekId();
        output["metadata"]["data_color_id"] = GetDataColorId();

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
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    Direction ShulkerEntity::GetDataAttachFaceId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<Direction>(metadata.at("data_attach_face_id"));
    }

#if PROTOCOL_VERSION < 755 /* < 1.17 */
    std::optional<Position> ShulkerEntity::GetDataAttachPosId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<std::optional<Position>>(metadata.at("data_attach_pos_id"));
    }
#endif

    char ShulkerEntity::GetDataPeekId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_peek_id"));
    }

    char ShulkerEntity::GetDataColorId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_color_id"));
    }


    void ShulkerEntity::SetDataAttachFaceId(const Direction data_attach_face_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_attach_face_id"] = data_attach_face_id;
    }

#if PROTOCOL_VERSION < 755 /* < 1.17 */
    void ShulkerEntity::SetDataAttachPosId(const std::optional<Position>& data_attach_pos_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_attach_pos_id"] = data_attach_pos_id;
    }
#endif

    void ShulkerEntity::SetDataPeekId(const char data_peek_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_peek_id"] = data_peek_id;
    }

    void ShulkerEntity::SetDataColorId(const char data_color_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_color_id"] = data_color_id;
    }

}
