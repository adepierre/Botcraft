#include "botcraft/Game/Entities/entities/monster/ShulkerEntity.hpp"

namespace Botcraft
{
    ShulkerEntity::ShulkerEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataAttachFaceId(Direction::Down);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        SetDataAttachPosId(std::optional<Position>());
#endif
        SetDataPeekId(0);
        SetDataColorId(16);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 30.0) });
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


    Direction ShulkerEntity::GetDataAttachFaceId() const
    {
        return GetMetadata<Direction>(BOTCRAFT_ENTITY_METADATA_INDEX("data_attach_face_id"));
    }

#if PROTOCOL_VERSION < 755 /* < 1.17 */
    std::optional<Position> ShulkerEntity::GetDataAttachPosId() const
    {
        return GetMetadata<std::optional<Position>>(BOTCRAFT_ENTITY_METADATA_INDEX("data_attach_pos_id"));
    }
#endif

    char ShulkerEntity::GetDataPeekId() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_peek_id"));
    }

    char ShulkerEntity::GetDataColorId() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_color_id"));
    }


    void ShulkerEntity::SetDataAttachFaceId(const Direction data_attach_face_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_attach_face_id"), data_attach_face_id);
    }

#if PROTOCOL_VERSION < 755 /* < 1.17 */
    void ShulkerEntity::SetDataAttachPosId(const std::optional<Position>& data_attach_pos_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_attach_pos_id"), data_attach_pos_id);
    }
#endif

    void ShulkerEntity::SetDataPeekId(const char data_peek_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_peek_id"), data_peek_id);
    }

    void ShulkerEntity::SetDataColorId(const char data_color_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_color_id"), data_color_id);
    }


    double ShulkerEntity::GetWidthImpl() const
    {
        return 1.0;
    }

    double ShulkerEntity::GetHeightImpl() const
    {
        return 1.0;
    }

}
