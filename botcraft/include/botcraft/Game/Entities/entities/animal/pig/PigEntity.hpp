#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class PigEntity : public AnimalEntity
    {
    protected:
        static constexpr int metadata_count = 2;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        PigEntity();
        virtual ~PigEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        bool GetDataSaddleId() const;
#endif
        int GetDataBoostTime() const;
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        int GetDataVariantId() const;
#endif

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        void SetDataSaddleId(const bool data_saddle_id);
#endif
        void SetDataBoostTime(const int data_boost_time);
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        void SetDataVariantId(const int data_variant_id);
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
