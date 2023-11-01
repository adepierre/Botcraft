#pragma once

#include "botcraft/Game/Entities/entities/decoration/HangingEntity.hpp"

namespace Botcraft
{
    class PaintingEntity : public HangingEntity
    {
    protected:
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
#else
        static constexpr int metadata_count = 0;
#endif
        static constexpr int hierarchy_metadata_count = HangingEntity::metadata_count + HangingEntity::hierarchy_metadata_count;

    public:
        PaintingEntity();
        virtual ~PaintingEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataPaintingVariantId() const;

        void SetDataPaintingVariantId(const int data_painting_variant_id);
#endif

    };
}
