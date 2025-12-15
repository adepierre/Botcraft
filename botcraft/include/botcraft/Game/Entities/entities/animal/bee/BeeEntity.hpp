#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class BeeEntity : public AnimalEntity
    {
    protected:
        static constexpr int metadata_count = 2;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        BeeEntity();
        virtual ~BeeEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        char GetDataFlagsId() const;
#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
        int GetDataRemainingAngerTime() const;
#else
        long long int GetDataAngerEndTime() const;
#endif

        void SetDataFlagsId(const char data_flags_id);
#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
        void SetDataRemainingAngerTime(const int data_remaining_anger_time);
#else
        void SetDataAngerEndTime(const long long int data_anger_end_time);
#endif

        // Attribute stuff
        double GetAttributeFlyingSpeedValue() const;
        double GetAttributeAttackDamageValue() const;

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
