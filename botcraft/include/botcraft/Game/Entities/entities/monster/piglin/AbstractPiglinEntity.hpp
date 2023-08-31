#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
#pragma once

#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"

namespace Botcraft
{
    class AbstractPiglinEntity : public MonsterEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = MonsterEntity::metadata_count + MonsterEntity::hierarchy_metadata_count;

    public:
        AbstractPiglinEntity();
        virtual ~AbstractPiglinEntity();

        virtual bool IsAbstractPiglin() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        bool GetDataImmuneToZombification() const;

        void SetDataImmuneToZombification(const bool data_immune_to_zombification);

    };
}
#endif
