#if PROTOCOL_VERSION > 404
#pragma once

#include "botcraft/Game/Entities/entities/TamableAnimalEntity.hpp"

namespace Botcraft
{
    class CatEntity : public TamableAnimalEntity
    {
    protected:
        static constexpr int metadata_count = 4;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = TamableAnimalEntity::metadata_count + TamableAnimalEntity::hierarchy_metadata_count;

    public:
        CatEntity();
        virtual ~CatEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual nlohmann::json Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataTypeId() const;
        bool GetIsLying() const;
        bool GetRelaxStateOne() const;
        int GetDataCollarColor() const;

        void SetDataTypeId(const int data_type_id);
        void SetIsLying(const bool is_lying);
        void SetRelaxStateOne(const bool relax_state_one);
        void SetDataCollarColor(const int data_collar_color);

    };
}
#endif
