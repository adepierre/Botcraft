#pragma once

#include "botcraft/Game/Entities/entities/TamableAnimalEntity.hpp"

namespace Botcraft
{
    class WolfEntity : public TamableAnimalEntity
    {
    protected:
#if PROTOCOL_VERSION > 578
        static constexpr int metadata_count = 3;
#elif PROTOCOL_VERSION > 498
        static constexpr int metadata_count = 2;
#else
        static constexpr int metadata_count = 3;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = TamableAnimalEntity::metadata_count + TamableAnimalEntity::hierarchy_metadata_count;

    public:
        WolfEntity();
        virtual ~WolfEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;


#if PROTOCOL_VERSION < 499
        float GetDataHealthId() const;
#endif
        bool GetDataInterestedId() const;
        int GetDataCollarColor() const;
#if PROTOCOL_VERSION > 578
        int GetDataRemainingAngerTime() const;
#endif

#if PROTOCOL_VERSION < 499
        void SetDataHealthId(const float data_health_id);
#endif
        void SetDataInterestedId(const bool data_interested_id);
        void SetDataCollarColor(const int data_collar_color);
#if PROTOCOL_VERSION > 578
        void SetDataRemainingAngerTime(const int data_remaining_anger_time);
#endif

    };
}
