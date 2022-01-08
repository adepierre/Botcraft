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


    nlohmann::json SpellcasterIllagerEntity::Serialize() const
    {
        nlohmann::json output = AbstractIllagerEntity::Serialize();

        output["data_spell_casting_id"] = GetDataSpellCastingId();

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
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char SpellcasterIllagerEntity::GetDataSpellCastingId() const
    {
        return std::any_cast<char>(metadata.at("data_spell_casting_id"));
    }


    void SpellcasterIllagerEntity::SetDataSpellCastingId(const char data_spell_casting_id)
    {
        metadata["data_spell_casting_id"] = data_spell_casting_id;
    }

}
