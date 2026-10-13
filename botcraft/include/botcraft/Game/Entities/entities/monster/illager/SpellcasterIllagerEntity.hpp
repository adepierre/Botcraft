#pragma once

#include "botcraft/Game/Entities/entities/monster/illager/AbstractIllagerEntity.hpp"

namespace Botcraft
{
    class SpellcasterIllagerEntity : public AbstractIllagerEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_spell_casting_id"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AbstractIllagerEntity::metadata_count + AbstractIllagerEntity::hierarchy_metadata_count;

    public:
        SpellcasterIllagerEntity();
        virtual ~SpellcasterIllagerEntity();

        virtual bool IsSpellcasterIllager() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        char GetDataSpellCastingId() const;

        void SetDataSpellCastingId(const char data_spell_casting_id);

    };
}
