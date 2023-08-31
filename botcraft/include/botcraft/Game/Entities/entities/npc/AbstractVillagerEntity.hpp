#if PROTOCOL_VERSION > 477 /* > 1.14 */
#pragma once

#include "botcraft/Game/Entities/entities/AgeableMobEntity.hpp"

namespace Botcraft
{
    class AbstractVillagerEntity : public AgeableMobEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AgeableMobEntity::metadata_count + AgeableMobEntity::hierarchy_metadata_count;

    public:
        AbstractVillagerEntity();
        virtual ~AbstractVillagerEntity();

        virtual bool IsAbstractVillager() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataUnhappyCounter() const;

        void SetDataUnhappyCounter(const int data_unhappy_counter);

    };
}
#endif
