#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "botcraft/Game/Entities/entities/DisplayEntity.hpp"

namespace Botcraft
{
    class DisplayBlockDisplayEntity : public DisplayEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_block_state_id"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = DisplayEntity::metadata_count + DisplayEntity::hierarchy_metadata_count;

    public:
        DisplayBlockDisplayEntity();
        virtual ~DisplayBlockDisplayEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetDataBlockStateId() const;

        void SetDataBlockStateId(const int data_block_state_id);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;
    };
}
#endif
