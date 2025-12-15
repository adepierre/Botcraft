#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#pragma once

#include "botcraft/Game/Entities/entities/monster/illager/AbstractIllagerEntity.hpp"

namespace Botcraft
{
    class PillagerEntity : public AbstractIllagerEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AbstractIllagerEntity::metadata_count + AbstractIllagerEntity::hierarchy_metadata_count;

    public:
        PillagerEntity();
        virtual ~PillagerEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        bool GetIsChargingCrossbow() const;

        void SetIsChargingCrossbow(const bool is_charging_crossbow);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
