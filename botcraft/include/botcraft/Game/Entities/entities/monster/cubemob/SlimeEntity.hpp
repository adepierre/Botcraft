#pragma once

#if PROTOCOL_VERSION < 776 /* < 26.2 */
#include "botcraft/Game/Entities/entities/MobEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/monster/cubemob/AbstractCubeMobEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION < 776 /* < 26.2 */
    class SlimeEntity : public MobEntity
#else
    class SlimeEntity : public AbstractCubeMobEntity
#endif
    {
    protected:
#if PROTOCOL_VERSION < 776 /* < 26.2 */
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = MobEntity::metadata_count + MobEntity::hierarchy_metadata_count;
#else
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractCubeMobEntity::metadata_count + AbstractCubeMobEntity::hierarchy_metadata_count;
#endif

    public:
        SlimeEntity();
        virtual ~SlimeEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


#if PROTOCOL_VERSION < 776 /* < 26.2 */
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetIdSize() const;

        void SetIdSize(const int id_size);

    protected:
        int GetIdSizeImpl() const;
        void SizeChanged(const int new_size);
#else
    protected:
        virtual void SizeChanged(const int new_size) override;
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;
    };
}
