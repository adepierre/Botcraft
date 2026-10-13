#pragma once

#include "botcraft/Game/Entities/entities/decoration/HangingEntity.hpp"

namespace Botcraft
{
    class PaintingEntity : public HangingEntity
    {
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_painting_variant_id"),
        };
#endif
    protected:
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
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

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetDataPaintingVariantId() const;

        void SetDataPaintingVariantId(const int data_painting_variant_id);
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
