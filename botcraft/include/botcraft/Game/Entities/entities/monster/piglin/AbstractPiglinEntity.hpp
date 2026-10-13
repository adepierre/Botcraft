#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
#pragma once

#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"

namespace Botcraft
{
    class AbstractPiglinEntity : public MonsterEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_immune_to_zombification"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = MonsterEntity::metadata_count + MonsterEntity::hierarchy_metadata_count;

    public:
        AbstractPiglinEntity();
        virtual ~AbstractPiglinEntity();

        virtual bool IsAbstractPiglin() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        bool GetDataImmuneToZombification() const;

        void SetDataImmuneToZombification(const bool data_immune_to_zombification);

    };
}
#endif
