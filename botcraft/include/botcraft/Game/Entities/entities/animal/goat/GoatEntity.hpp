#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class GoatEntity : public AnimalEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_is_screaming_goat"),
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            std::string_view("data_has_left_horn"),
            std::string_view("data_has_right_horn"),
#endif
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        GoatEntity();
        virtual ~GoatEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
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

        // Attribute stuff
        double GetAttributeAttackDamageValue() const;

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
