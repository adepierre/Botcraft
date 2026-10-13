#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "botcraft/Game/Entities/entities/AvatarEntity.hpp"

#include "protocolCraft/Types/Components/DataComponentTypeResolvableProfile.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace Botcraft
{
    class MannequinEntity : public AvatarEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_profile"),
            std::string_view("data_immovable"),
            std::string_view("data_description"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AvatarEntity::metadata_count + AvatarEntity::hierarchy_metadata_count;

    public:
        MannequinEntity();
        virtual ~MannequinEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        ProtocolCraft::Components::DataComponentTypeResolvableProfile GetDataProfile() const;
        bool GetDataImmovable() const;
        std::optional<ProtocolCraft::Chat> GetDataDescription() const;

        void SetDataProfile(const ProtocolCraft::Components::DataComponentTypeResolvableProfile& data_profile);
        void SetDataImmovable(const bool data_immovable);
        void SetDataDescription(const std::optional<ProtocolCraft::Chat>& data_description);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
