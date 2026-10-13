#pragma once

#include "botcraft/Game/Entities/entities/ambient/AmbientCreatureEntity.hpp"

namespace Botcraft
{
    class BatEntity : public AmbientCreatureEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_id_flags"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AmbientCreatureEntity::metadata_count + AmbientCreatureEntity::hierarchy_metadata_count;

    public:
        BatEntity();
        virtual ~BatEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        char GetDataIdFlags() const;

        void SetDataIdFlags(const char data_id_flags);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
