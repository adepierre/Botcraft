#if PROTOCOL_VERSION > 477 /* > 1.14 */
#pragma once

#include "botcraft/Game/Entities/entities/AgeableMobEntity.hpp"

namespace Botcraft
{
    class AbstractVillagerEntity : public AgeableMobEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_unhappy_counter"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AgeableMobEntity::metadata_count + AgeableMobEntity::hierarchy_metadata_count;

    public:
        AbstractVillagerEntity();
        virtual ~AbstractVillagerEntity();

        virtual bool IsAbstractVillager() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetDataUnhappyCounter() const;

        void SetDataUnhappyCounter(const int data_unhappy_counter);

    };
}
#endif
