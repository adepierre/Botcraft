#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#pragma once

#if PROTOCOL_VERSION < 771 /* < 1.21.6 */
#include "botcraft/Game/Entities/entities/FlyingMobEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/MobEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION < 771 /* < 1.21.6 */
    class PhantomEntity : public FlyingMobEntity
#else
    class PhantomEntity : public MobEntity
#endif
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
#if PROTOCOL_VERSION < 771 /* < 1.21.6 */
        static constexpr int hierarchy_metadata_count = FlyingMobEntity::metadata_count + FlyingMobEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = MobEntity::metadata_count + MobEntity::hierarchy_metadata_count;
#endif

    public:
        PhantomEntity();
        virtual ~PhantomEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetIdSize() const;

        void SetIdSize(const int id_size);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
