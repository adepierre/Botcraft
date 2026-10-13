#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
#include "botcraft/Game/Entities/entities/monster/cubemob/AbstractCubeMobEntity.hpp"
#include "botcraft/Utilities/Logger.hpp"

namespace Botcraft
{
    AbstractCubeMobEntity::AbstractCubeMobEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    void AbstractCubeMobEntity::OnMetadataChangedImpl(const int index)
    {
        if (index < hierarchy_metadata_count)
        {
            AgeableMobEntity::OnMetadataChangedImpl(index);
        }
        else if (index == BOTCRAFT_ENTITY_METADATA_INDEX("id_size"))
        {
            SizeChanged(GetMetadataImpl<int>(index));
#if USE_GUI
            OnSizeUpdated();
#endif
        }
    }

    int AbstractCubeMobEntity::GetIdSize() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetIdSizeImpl();
    }


    void AbstractCubeMobEntity::SetIdSize(const int id_size)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("id_size"), id_size);
    }


    int AbstractCubeMobEntity::GetIdSizeImpl() const
    {
        return GetMetadataImpl<int>(BOTCRAFT_ENTITY_METADATA_INDEX("id_size"));
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
