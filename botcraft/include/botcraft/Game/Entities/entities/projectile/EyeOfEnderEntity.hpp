#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "protocolCraft/Types/Item/Slot.hpp"
#endif

namespace Botcraft
{
    class EyeOfEnderEntity : public Entity
    {
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_item_stack"),
        };
#endif
    protected:
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
#else
        static constexpr int metadata_count = 0;
#endif
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        EyeOfEnderEntity();
        virtual ~EyeOfEnderEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        ProtocolCraft::Slot GetDataItemStack() const;

        void SetDataItemStack(const ProtocolCraft::Slot& data_item_stack);
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
