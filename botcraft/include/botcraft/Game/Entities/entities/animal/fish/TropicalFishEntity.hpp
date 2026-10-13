#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/fish/AbstractSchoolingFishEntity.hpp"

namespace Botcraft
{
    class TropicalFishEntity : public AbstractSchoolingFishEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_id_type_variant"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AbstractSchoolingFishEntity::metadata_count + AbstractSchoolingFishEntity::hierarchy_metadata_count;

    public:
        TropicalFishEntity();
        virtual ~TropicalFishEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetDataIdTypeVariant() const;

        void SetDataIdTypeVariant(const int data_id_type_variant);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
