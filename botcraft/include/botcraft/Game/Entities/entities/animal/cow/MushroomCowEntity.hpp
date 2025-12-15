#pragma once

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
#include "botcraft/Game/Entities/entities/animal/cow/CowEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/animal/cow/AbstractCowEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    class MushroomCowEntity : public CowEntity
#else
    class MushroomCowEntity : public AbstractCowEntity
#endif
    {
    protected:
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
#else
        static constexpr int metadata_count = 0;
#endif
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        static constexpr int hierarchy_metadata_count = CowEntity::metadata_count + CowEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = AbstractCowEntity::metadata_count + AbstractCowEntity::hierarchy_metadata_count;
#endif

    public:
        MushroomCowEntity();
        virtual ~MushroomCowEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        std::string GetDataType() const;

        void SetDataType(const std::string& data_type);
#else
        int GetDataType() const;

        void SetDataType(const int data_type);
#endif
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
