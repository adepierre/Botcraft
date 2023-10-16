#include "botcraft/Game/Entities/entities/monster/SpellcasterIllagerEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, SpellcasterIllagerEntity::metadata_count> SpellcasterIllagerEntity::metadata_names{ {
        "data_spell_casting_id",
    } };

    SpellcasterIllagerEntity::SpellcasterIllagerEntity()
    {
        // Initialize all metadata with default values
        SetDataSpellCastingId(0);
    }

    SpellcasterIllagerEntity::~SpellcasterIllagerEntity()
    {

    }

    bool SpellcasterIllagerEntity::IsSpellcasterIllager() const
    {
        return true;
    }


    ProtocolCraft::Json::Value SpellcasterIllagerEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractIllagerEntity::Serialize();

        output["metadata"]["data_spell_casting_id"] = GetDataSpellCastingId();

        return output;
    }


    void SpellcasterIllagerEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractIllagerEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char SpellcasterIllagerEntity::GetDataSpellCastingId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_spell_casting_id"));
    }


    void SpellcasterIllagerEntity::SetDataSpellCastingId(const char data_spell_casting_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_spell_casting_id"] = data_spell_casting_id;
    }

}
