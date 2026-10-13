#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class HappyGhastEntity : public AnimalEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("is_leash_holder"),
            std::string_view("stays_still"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        HappyGhastEntity();
        virtual ~HappyGhastEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        bool GetIsLeashHolder() const;
        bool GetStaysStill() const;

        void SetIsLeashHolder(const int is_leahs_holder);
        void SetStaysStill(const int stays_still);

        // Attribute stuff
        double GetAttributeFlyingSpeedValue() const;

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
