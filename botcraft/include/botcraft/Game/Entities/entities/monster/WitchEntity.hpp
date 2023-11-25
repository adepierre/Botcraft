#pragma once

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "botcraft/Game/Entities/entities/raid/RaiderEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/MobEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    class WitchEntity : public RaiderEntity
#else
    class WitchEntity : public MobEntity
#endif
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        static constexpr int hierarchy_metadata_count = RaiderEntity::metadata_count + RaiderEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = MobEntity::metadata_count + MobEntity::hierarchy_metadata_count;
#endif

    public:
        WitchEntity();
        virtual ~WitchEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        bool GetDataUsingItem() const;

        void SetDataUsingItem(const bool data_using_item);

        // Attribute stuff
        // 5cd17e52-a79a-43d3-a529-90fde04b181e
        static constexpr std::array<unsigned char, 16> speed_modifier_drinking_uuid = { 0x5C, 0xD1, 0x7E, 0x52, 0xA7, 0x9A, 0x43, 0xD3, 0xA5, 0x29, 0x90, 0xFD, 0xE0, 0x4B, 0x18, 0x1E };


    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
