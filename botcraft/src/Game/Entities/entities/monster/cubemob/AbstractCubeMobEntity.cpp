#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
#include "botcraft/Game/Entities/entities/monster/cubemob/AbstractCubeMobEntity.hpp"
#include "botcraft/Utilities/Logger.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, AbstractCubeMobEntity::metadata_count> AbstractCubeMobEntity::metadata_names{ {
        "id_size",
    } };

    AbstractCubeMobEntity::AbstractCubeMobEntity()
    {
        // Initialize all metadata with default values
        SetIdSize(1);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.2) });
    }

    AbstractCubeMobEntity::~AbstractCubeMobEntity()
    {

    }

    bool AbstractCubeMobEntity::IsAbstractCubeMob() const
    {
        return true;
    }


    ProtocolCraft::Json::Value AbstractCubeMobEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AgeableMobEntity::Serialize();

        output["metadata"]["id_size"] = GetIdSize();

        return output;
    }


    void AbstractCubeMobEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AgeableMobEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int AbstractCubeMobEntity::GetIdSize() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetIdSizeImpl();
    }


    void AbstractCubeMobEntity::SetIdSize(const int id_size)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["id_size"] = id_size;
        SizeChanged(id_size);
#if USE_GUI
        OnSizeUpdated();
#endif
    }


    int AbstractCubeMobEntity::GetIdSizeImpl() const
    {
        return std::any_cast<bool>(metadata.at("id_size"));
    }

    void AbstractCubeMobEntity::SizeChanged(const int new_size)
    {
        auto it = attributes.find(EntityAttribute::Type::MaxHealth);
        if (it != attributes.end())
        {
            it->second.SetBaseValue(static_cast<double>(new_size) * new_size);
        }
        else
        {
            LOG_WARNING("Trying to set attribute base value for " << EntityAttribute::Type::MaxHealth << " for a CubeMob but it doesn't have this attribute");
        }

        it = attributes.find(EntityAttribute::Type::MovementSpeed);
        if (it != attributes.end())
        {
            it->second.SetBaseValue(0.2 + 0.1 * new_size);
        }
        else
        {
            LOG_WARNING("Trying to set attribute base value for " << EntityAttribute::Type::MovementSpeed << " for a CubeMob but it doesn't have this attribute");
        }
    }
}
#endif
