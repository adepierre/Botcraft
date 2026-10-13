#pragma once

#if PROTOCOL_VERSION < 771 /* < 1.21.6 */
#include "botcraft/Game/Entities/entities/FlyingMobEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/MobEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION < 771 /* < 1.21.6 */
    class GhastEntity : public FlyingMobEntity
#else
    class GhastEntity : public MobEntity
#endif
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_is_charging"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
#if PROTOCOL_VERSION < 771 /* < 1.21.6 */
        static constexpr int hierarchy_metadata_count = FlyingMobEntity::metadata_count + FlyingMobEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = MobEntity::metadata_count + MobEntity::hierarchy_metadata_count;
#endif

    public:
        GhastEntity();
        virtual ~GhastEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        bool GetDataIsCharging() const;

        void SetDataIsCharging(const bool data_is_charging);


#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        // Attribute stuff
        double GetAttributeFlyingSpeedValue() const;
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
