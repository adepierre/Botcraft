#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/fish/AbstractSchoolingFishEntity.hpp"

namespace Botcraft
{
    class SalmonEntity : public AbstractSchoolingFishEntity
    {
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_type"),
        };
#endif
    protected:
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        static constexpr int metadata_count = 0;
#else
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
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
#if PROTOCOL_VERSION < 769 /* < 1.21.4 */
        std::string GetDataType() const;
        void SetDataType(const std::string& data_type);
#else
        int GetDataType() const;
        void SetDataType(const int data_type);
#endif
#endif

    protected:
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        void OnMetadataChangedImpl(const int index) override;
#if PROTOCOL_VERSION < 769 /* < 1.21.4 */
        const std::string& GetDataTypeImpl() const;
#else
        int GetDataTypeImpl() const;
#endif
        double GetScaleImpl() const;
#endif
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
