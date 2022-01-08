#pragma once

#include "botcraft/Game/Entities/entities/monster/AbstractIllagerEntity.hpp"

namespace Botcraft
{
    class SpellcasterIllagerEntity : public AbstractIllagerEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AbstractIllagerEntity::metadata_count + AbstractIllagerEntity::hierarchy_metadata_count;

    public:
        SpellcasterIllagerEntity();
        virtual ~SpellcasterIllagerEntity();

        virtual bool IsSpellcasterIllager() const override;

        virtual nlohmann::json Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        char GetDataSpellCastingId() const;

        void SetDataSpellCastingId(const char data_spell_casting_id);

    };
}
