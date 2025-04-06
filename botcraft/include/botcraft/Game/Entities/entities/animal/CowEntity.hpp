#pragma once

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/animal/AbstractCowEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    class CowEntity : public AnimalEntity
#else
    class CowEntity : public AbstractCowEntity
#endif
    {
    protected:
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;
#else
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AbstractCowEntity::metadata_count + AbstractCowEntity::hierarchy_metadata_count;
#endif

    public:
        CowEntity();
        virtual ~CowEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataVariantId() const;

        void SetDataVariantId(const int data_variant_id);
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
