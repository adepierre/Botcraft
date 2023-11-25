#include "botcraft/Game/Entities/entities/monster/SlimeEntity.hpp"
#include "botcraft/Utilities/Logger.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, SlimeEntity::metadata_count> SlimeEntity::metadata_names{ {
        "id_size",
    } };

    SlimeEntity::SlimeEntity()
    {
        // Initialize all metadata with default values
        SetIdSize(1);
    }

    SlimeEntity::~SlimeEntity()
    {

    }


    std::string SlimeEntity::GetName() const
    {
        return "slime";
    }

    EntityType SlimeEntity::GetType() const
    {
        return EntityType::Slime;
    }


    std::string SlimeEntity::GetClassName()
    {
        return "slime";
    }

    EntityType SlimeEntity::GetClassType()
    {
        return EntityType::Slime;
    }


    ProtocolCraft::Json::Value SlimeEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MobEntity::Serialize();

        output["metadata"]["id_size"] = GetIdSize();

        return output;
    }


    void SlimeEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MobEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            const std::string& metadata_name = metadata_names[index - hierarchy_metadata_count];
            metadata[metadata_name] = value;
            if (metadata_name == "id_size")
            {
                SizeChanged(std::any_cast<int>(value));
#if USE_GUI
                OnSizeUpdated();
#endif
            }
        }
    }

    int SlimeEntity::GetIdSize() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetIdSizeImpl();
    }


    void SlimeEntity::SetIdSize(const int id_size)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["id_size"] = id_size;
        SizeChanged(id_size);
#if USE_GUI
        OnSizeUpdated();
#endif
    }

    int SlimeEntity::GetIdSizeImpl() const
    {
        return std::any_cast<int>(metadata.at("id_size"));
    }

    void SlimeEntity::SizeChanged(const int new_size)
    {
        auto it = attributes.find(EntityAttribute::Type::MaxHealth);
        if (it != attributes.end())
        {
            it->second.SetBaseValue(static_cast<double>(new_size) * new_size);
        }
        else
        {
            LOG_WARNING("Trying to set attribute base value for " << EntityAttribute::Type::MaxHealth << " for a " << GetName() << " but it doesn't have this attribute");
        }

        it = attributes.find(EntityAttribute::Type::MovementSpeed);
        if (it != attributes.end())
        {
            it->second.SetBaseValue(0.2 + 0.1 * new_size);
        }
        else
        {
            LOG_WARNING("Trying to set attribute base value for " << EntityAttribute::Type::MovementSpeed << " for a " << GetName() << " but it doesn't have this attribute");
        }

        it = attributes.find(EntityAttribute::Type::AttackDamage);
        if (it != attributes.end())
        {
            it->second.SetBaseValue(static_cast<double>(new_size));
        }
        else
        {
            LOG_WARNING("Trying to set attribute base value for " << EntityAttribute::Type::AttackDamage << " for a slime but it doesn't have this attribute");
        }
    }

    double SlimeEntity::GetWidthImpl() const
    {
        return 0.255 * 2.04 * GetIdSizeImpl();
    }

    double SlimeEntity::GetHeightImpl() const
    {
        return 0.255 * 2.04 * GetIdSizeImpl();
    }

}
