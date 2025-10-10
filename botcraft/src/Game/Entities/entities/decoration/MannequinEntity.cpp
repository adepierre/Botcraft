#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "botcraft/Game/Entities/entities/decoration/MannequinEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, MannequinEntity::metadata_count> MannequinEntity::metadata_names{ {
        "data_profile",
        "data_immovable",
        "data_description",
    } };

    MannequinEntity::MannequinEntity()
    {
        // Initialize all metadata with default values
        SetDataProfile(ProtocolCraft::Components::DataComponentTypeResolvableProfile()
            .SetUnpack(ProtocolCraft::Either<ProtocolCraft::GameProfile, ProtocolCraft::Components::PartialResolvableProfile>()
                .SetRight(ProtocolCraft::Components::PartialResolvableProfile()
                    .SetName(std::nullopt)
                    .SetUuid(std::nullopt)
                    .SetProperties({})
                )
            )
            .SetSkinPatch(ProtocolCraft::Components::PlayerSkinPatch()
                .SetBody(std::nullopt)
                .SetCape(std::nullopt)
                .SetElytra(std::nullopt)
                .SetModel(std::nullopt)
            )
        );
        SetDataImmovable(false);
        SetDataDescription(ProtocolCraft::Chat()); // TODO: Default "NPC" string
    }

    MannequinEntity::~MannequinEntity()
    {

    }


    std::string MannequinEntity::GetName() const
    {
        return "mannequin";
    }

    EntityType MannequinEntity::GetType() const
    {
        return EntityType::Mannequin;
    }


    std::string MannequinEntity::GetClassName()
    {
        return "mannequin";
    }

    EntityType MannequinEntity::GetClassType()
    {
        return EntityType::Mannequin;
    }


    ProtocolCraft::Json::Value MannequinEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = LivingEntity::Serialize();

        output["metadata"]["data_profile"] = GetDataProfile().Serialize();
        output["metadata"]["data_immovable"] = GetDataImmovable();
        output["metadata"]["data_description"] = GetDataDescription().has_value() ? GetDataDescription().value().Serialize() : nullptr;

        return output;
    }


    void MannequinEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AvatarEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    const ProtocolCraft::Components::DataComponentTypeResolvableProfile& MannequinEntity::GetDataProfile() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<const ProtocolCraft::Components::DataComponentTypeResolvableProfile&>(metadata.at("data_profile"));
    }

    bool MannequinEntity::GetDataImmovable() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_immovable"));
    }

    const std::optional<ProtocolCraft::Chat>& MannequinEntity::GetDataDescription() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<const std::optional<ProtocolCraft::Chat>&>(metadata.at("data_description"));
    }


    void MannequinEntity::SetDataProfile(const ProtocolCraft::Components::DataComponentTypeResolvableProfile& data_profile)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_profile"] = data_profile;
    }

    void MannequinEntity::SetDataImmovable(const bool data_immovable)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_immovable"] = data_immovable;
    }

    void MannequinEntity::SetDataDescription(const std::optional<ProtocolCraft::Chat>& data_description)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_description"] = data_description;
    }


    double MannequinEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double MannequinEntity::GetHeightImpl() const
    {
        return 1.8;
    }

}
#endif
