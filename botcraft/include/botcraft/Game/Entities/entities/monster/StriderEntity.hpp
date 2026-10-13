#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class StriderEntity : public AnimalEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_boost_time"),
            std::string_view("data_suffocating"),
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
            std::string_view("data_saddle_id"),
#endif
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
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
        int GetDataBoostTime() const;
        bool GetDataSuffocating() const;
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        bool GetDataSaddleId() const;
#endif

        void SetDataBoostTime(const int data_boost_time);
        void SetDataSuffocating(const bool data_suffocating);
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        void SetDataSaddleId(const bool data_saddle_id);
#endif

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
