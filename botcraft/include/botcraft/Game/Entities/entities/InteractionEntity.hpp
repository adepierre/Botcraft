#if PROTOCOL_VERSION > 761
#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"

namespace Botcraft
{
    class InteractionEntity : public Entity
    {
    protected:
        static constexpr int metadata_count = 3;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        InteractionEntity();
        virtual ~InteractionEntity();

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

        float GetDataWidthId() const;
        float GetDataHeightId() const;
        bool GetDataResponseId() const;
        
        void SetDataWidthId(const float data_width_id);
        void SetDataHeightId(const float data_height_id);
        void SetDataResponseId(const bool data_response_id);
        
    };
}
#endif
