#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class StriderEntity : public AnimalEntity
    {
    protected:
        static constexpr int metadata_count = 3;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        StriderEntity();
        virtual ~StriderEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataBoostTime() const;
        bool GetDataSuffocating() const;
        bool GetDataSaddleId() const;

        void SetDataBoostTime(const int data_boost_time);
        void SetDataSuffocating(const bool data_suffocating);
        void SetDataSaddleId(const bool data_saddle_id);

        // Attribute stuff
#if PROTOCOL_VERSION < 767 /* < 1.21 */
        // 9e362924-01de-4ddd-a2b2-d0f7a405a174
        static constexpr std::array<unsigned char, 16> suffocating_modifier_key= { 0x9E, 0x36, 0x29, 0x24, 0x1, 0xDE, 0x4D, 0xDD, 0xA2, 0xB2, 0xD0, 0xF7, 0xA4, 0x5, 0xA1, 0x74 };
#else
        inline static const std::string suffocating_modifier_key = "minecraft:suffocating";
#endif


    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
