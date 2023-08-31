#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class GoatEntity : public AnimalEntity
    {
    protected:
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        static constexpr int metadata_count = 3;
#else
        static constexpr int metadata_count = 1;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        GoatEntity();
        virtual ~GoatEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        bool GetDataIsScreamingGoat() const;
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        bool GetDataHasLeftHorn() const;
        bool GetDataHasRightHorn() const;
#endif

        void SetDataIsScreamingGoat(const bool data_is_screaming_goat);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        void SetDataHasLeftHorn(const bool data_has_left_horn);
        void SetDataHasRightHorn(const bool data_has_right_horn);
#endif

    };
}
#endif
