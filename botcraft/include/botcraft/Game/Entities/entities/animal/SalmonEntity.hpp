#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/AbstractSchoolingFishEntity.hpp"

namespace Botcraft
{
    class SalmonEntity : public AbstractSchoolingFishEntity
    {
    protected:
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        static constexpr int metadata_count = 0;
#else
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
#endif
        static constexpr int hierarchy_metadata_count = AbstractSchoolingFishEntity::metadata_count + AbstractSchoolingFishEntity::hierarchy_metadata_count;

    public:
        SalmonEntity();
        virtual ~SalmonEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        const std::string& GetDataType() const;
        void SetDataType(const std::string& data_type);
#endif

    protected:
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        const std::string& GetDataTypeImpl() const;
        double GetScaleImpl() const;
#endif
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
