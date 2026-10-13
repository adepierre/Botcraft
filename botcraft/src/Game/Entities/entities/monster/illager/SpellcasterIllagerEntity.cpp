#include "botcraft/Game/Entities/entities/monster/illager/SpellcasterIllagerEntity.hpp"

namespace Botcraft
{
    SpellcasterIllagerEntity::SpellcasterIllagerEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    char SpellcasterIllagerEntity::GetDataSpellCastingId() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_spell_casting_id"));
    }


    void SpellcasterIllagerEntity::SetDataSpellCastingId(const char data_spell_casting_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_spell_casting_id"), data_spell_casting_id);
    }

}
