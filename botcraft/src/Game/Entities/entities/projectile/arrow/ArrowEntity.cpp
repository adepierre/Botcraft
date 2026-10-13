#include "botcraft/Game/Entities/entities/projectile/arrow/ArrowEntity.hpp"

namespace Botcraft
{
    ArrowEntity::ArrowEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetIdEffectColor(-1);
    }

    ArrowEntity::~ArrowEntity()
    {

    }


    std::string ArrowEntity::GetName() const
    {
        return "arrow";
    }

    EntityType ArrowEntity::GetType() const
    {
        return EntityType::Arrow;
    }


    std::string ArrowEntity::GetClassName()
    {
        return "arrow";
    }

    EntityType ArrowEntity::GetClassType()
    {
        return EntityType::Arrow;
    }


    ProtocolCraft::Json::Value ArrowEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractArrowEntity::Serialize();

        output["metadata"]["id_effect_color"] = GetIdEffectColor();

        return output;
    }


    int ArrowEntity::GetIdEffectColor() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("id_effect_color"));
    }


    void ArrowEntity::SetIdEffectColor(const int id_effect_color)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("id_effect_color"), id_effect_color);
    }


    double ArrowEntity::GetWidthImpl() const
    {
        return 0.5;
    }

    double ArrowEntity::GetHeightImpl() const
    {
        return 0.5;
    }

}
