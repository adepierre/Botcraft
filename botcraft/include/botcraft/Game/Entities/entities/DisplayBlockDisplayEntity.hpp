#if PROTOCOL_VERSION > 761
#pragma once

#include "botcraft/Game/Entities/entities/DisplayEntity.hpp"

namespace Botcraft
{
    class DisplayBlockDisplayEntity : public DisplayEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = DisplayEntity::metadata_count + DisplayEntity::hierarchy_metadata_count;

    public:
        DisplayBlockDisplayEntity();
        virtual ~DisplayBlockDisplayEntity();

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

        int GetDataBlockStateId() const;
        
        void SetDataBlockStateId(const int data_block_state_id);
        
    };
}
#endif
