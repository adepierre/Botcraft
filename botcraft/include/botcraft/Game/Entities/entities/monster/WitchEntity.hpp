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
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        bool GetDataUsingItem() const;

        void SetDataUsingItem(const bool data_using_item);

    };
}
