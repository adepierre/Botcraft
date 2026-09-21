#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once

#include "botcraft/Game/Entities/entities/decoration/BlockAttachedEntity.hpp"

namespace Botcraft
{
    class CushionEntity : public BlockAttachedEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = BlockAttachedEntity::metadata_count + BlockAttachedEntity::hierarchy_metadata_count;

    public:
        CushionEntity();
        virtual ~CushionEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataColor() const;

        void SetDataColor(const int data_color);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
