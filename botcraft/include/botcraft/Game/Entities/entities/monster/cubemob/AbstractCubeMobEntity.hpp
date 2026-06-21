#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
#pragma once

#include "botcraft/Game/Entities/entities/AgeableMobEntity.hpp"

namespace Botcraft
{
    class AbstractCubeMobEntity : public AgeableMobEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AgeableMobEntity::metadata_count + AgeableMobEntity::hierarchy_metadata_count;

    public:
        AbstractCubeMobEntity();
        virtual ~AbstractCubeMobEntity();

        virtual bool IsAbstractCubeMob() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetIdSize() const;

        void SetIdSize(const int id_size);

    protected:
        int GetIdSizeImpl() const;
        virtual void SizeChanged(const int new_size);

    };
}
#endif
