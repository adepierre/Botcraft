#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "botcraft/Game/Entities/entities/decoration/MannequinEntity.hpp"

namespace Botcraft
{
    MannequinEntity::MannequinEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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
        const std::optional<ProtocolCraft::Chat> data_description = GetDataDescription();
        output["metadata"]["data_description"] = data_description.has_value() ? data_description.value().Serialize() : nullptr;

        return output;
    }


    ProtocolCraft::Components::DataComponentTypeResolvableProfile MannequinEntity::GetDataProfile() const
    {
        return GetMetadata<ProtocolCraft::Components::DataComponentTypeResolvableProfile>(BOTCRAFT_ENTITY_METADATA_INDEX("data_profile"));
    }

    bool MannequinEntity::GetDataImmovable() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_immovable"));
    }

    std::optional<ProtocolCraft::Chat> MannequinEntity::GetDataDescription() const
    {
        return GetMetadata<std::optional<ProtocolCraft::Chat>>(BOTCRAFT_ENTITY_METADATA_INDEX("data_description"));
    }


    void MannequinEntity::SetDataProfile(const ProtocolCraft::Components::DataComponentTypeResolvableProfile& data_profile)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_profile"), data_profile);
    }

    void MannequinEntity::SetDataImmovable(const bool data_immovable)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_immovable"), data_immovable);
    }

    void MannequinEntity::SetDataDescription(const std::optional<ProtocolCraft::Chat>& data_description)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_description"), data_description);
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
