#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class AxolotlEntity : public AnimalEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_variant"),
            std::string_view("data_playing_dead"),
            std::string_view("from_bucket"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        AxolotlEntity();
        virtual ~AxolotlEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetDataVariant() const;
        bool GetDataPlayingDead() const;
        bool GetFromBucket() const;

        void SetDataVariant(const int data_variant);
        void SetDataPlayingDead(const bool data_playing_dead);
        void SetFromBucket(const bool from_bucket);

        // Attribute stuff
        double GetAttributeAttackDamageValue() const;

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
