#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/nautilus/AbstractNautilusEntity.hpp"

namespace Botcraft
{
    class ZombieNautilusEntity : public AbstractNautilusEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_variant_id"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
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
        int GetDataVariantId() const;

        void SetDataVariantId(const int data_variant_id);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
