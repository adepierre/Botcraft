#include "botcraft/Game/Entities/entities/monster/GuardianEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, GuardianEntity::metadata_count> GuardianEntity::metadata_names{ {
        "data_id_moving",
        "data_id_attack_target",
    } };

    GuardianEntity::GuardianEntity()
    {
        // Initialize all metadata with default values
        SetDataIdMoving(false);
        SetDataIdAttackTarget(0);
    }

    GuardianEntity::~GuardianEntity()
    {

    }


    std::string GuardianEntity::GetName() const
    {
        return "guardian";
    }

    EntityType GuardianEntity::GetType() const
    {
        return EntityType::Guardian;
    }


    std::string GuardianEntity::GetClassName()
    {
        return "guardian";
    }

    EntityType GuardianEntity::GetClassType()
    {
        return EntityType::Guardian;
    }


    ProtocolCraft::Json::Value GuardianEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_id_moving"] = GetDataIdMoving();
        output["metadata"]["data_id_attack_target"] = GetDataIdAttackTarget();

        return output;
    }


    void GuardianEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MonsterEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool GuardianEntity::GetDataIdMoving() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_id_moving"));
    }

    int GuardianEntity::GetDataIdAttackTarget() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_id_attack_target"));
    }


    void GuardianEntity::SetDataIdMoving(const bool data_id_moving)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_moving"] = data_id_moving;
    }

    void GuardianEntity::SetDataIdAttackTarget(const int data_id_attack_target)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_attack_target"] = data_id_attack_target;
    }


    double GuardianEntity::GetWidthImpl() const
    {
        return 0.85;
    }

    double GuardianEntity::GetHeightImpl() const
    {
        return 0.85;
    }

}
