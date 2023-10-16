#include "botcraft/Game/Entities/entities/monster/WitchEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, WitchEntity::metadata_count> WitchEntity::metadata_names{ {
        "data_using_item",
    } };

    WitchEntity::WitchEntity()
    {
        // Initialize all metadata with default values
        SetDataUsingItem(false);
    }

    WitchEntity::~WitchEntity()
    {

    }


    std::string WitchEntity::GetName() const
    {
        return "witch";
    }

    EntityType WitchEntity::GetType() const
    {
        return EntityType::Witch;
    }

    double WitchEntity::GetWidth() const
    {
        return 0.6;
    }

    double WitchEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string WitchEntity::GetClassName()
    {
        return "witch";
    }

    EntityType WitchEntity::GetClassType()
    {
        return EntityType::Witch;
    }


    ProtocolCraft::Json::Value WitchEntity::Serialize() const
    {
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        ProtocolCraft::Json::Value output = RaiderEntity::Serialize();
#else
        ProtocolCraft::Json::Value output = MobEntity::Serialize();
#endif

        output["metadata"]["data_using_item"] = GetDataUsingItem();

        return output;
    }


    void WitchEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
            RaiderEntity::SetMetadataValue(index, value);
#else
            MobEntity::SetMetadataValue(index, value);
#endif
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool WitchEntity::GetDataUsingItem() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_using_item"));
    }


    void WitchEntity::SetDataUsingItem(const bool data_using_item)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_using_item"] = data_using_item;
    }

}
