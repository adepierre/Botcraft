#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/nautilus/AbstractNautilusEntity.hpp"

namespace Botcraft
{
    class ZombieNautilusEntity : public AbstractNautilusEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AbstractNautilusEntity::metadata_count + AbstractNautilusEntity::hierarchy_metadata_count;

    public:
        ZombieNautilusEntity();
        virtual ~ZombieNautilusEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataVariantId() const;

        void SetDataVariantId(const int data_variant_id);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
