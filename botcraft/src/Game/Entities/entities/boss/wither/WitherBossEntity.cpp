#include "botcraft/Game/Entities/entities/boss/wither/WitherBossEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, WitherBossEntity::metadata_count> WitherBossEntity::metadata_names{ {
        "data_target_a",
        "data_target_b",
        "data_target_c",
        "data_id_inv",
    } };

    WitherBossEntity::WitherBossEntity()
    {
        // Initialize all metadata with default values
        SetDataTargetA(0);
        SetDataTargetB(0);
        SetDataTargetC(0);
        SetDataIdInv(0);
    }

    WitherBossEntity::~WitherBossEntity()
    {

    }


    std::string WitherBossEntity::GetName() const
    {
        return "WitherBoss";
    }

    EntityType WitherBossEntity::GetType() const
    {
        return EntityType::WitherBoss;
    }

    AABB WitherBossEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double WitherBossEntity::GetWidth() const
    {
        return 0.9;
    }

    double WitherBossEntity::GetHeight() const
    {
        return 3.5;
    }


    std::string WitherBossEntity::GetClassName()
    {
        return "WitherBoss";
    }

    EntityType WitherBossEntity::GetClassType()
    {
        return EntityType::WitherBoss;
    }


    nlohmann::json WitherBossEntity::Serialize() const
    {
        nlohmann::json output = MonsterEntity::Serialize();

        output["metadata"]["data_target_a"] = GetDataTargetA();
        output["metadata"]["data_target_b"] = GetDataTargetB();
        output["metadata"]["data_target_c"] = GetDataTargetC();
        output["metadata"]["data_id_inv"] = GetDataIdInv();

        return output;
    }


    void WitherBossEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MonsterEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int WitherBossEntity::GetDataTargetA() const
    {
        return std::any_cast<int>(metadata.at("data_target_a"));
    }

    int WitherBossEntity::GetDataTargetB() const
    {
        return std::any_cast<int>(metadata.at("data_target_b"));
    }

    int WitherBossEntity::GetDataTargetC() const
    {
        return std::any_cast<int>(metadata.at("data_target_c"));
    }

    int WitherBossEntity::GetDataIdInv() const
    {
        return std::any_cast<int>(metadata.at("data_id_inv"));
    }


    void WitherBossEntity::SetDataTargetA(const int data_target_a)
    {
        metadata["data_target_a"] = data_target_a;
    }

    void WitherBossEntity::SetDataTargetB(const int data_target_b)
    {
        metadata["data_target_b"] = data_target_b;
    }

    void WitherBossEntity::SetDataTargetC(const int data_target_c)
    {
        metadata["data_target_c"] = data_target_c;
    }

    void WitherBossEntity::SetDataIdInv(const int data_id_inv)
    {
        metadata["data_id_inv"] = data_id_inv;
    }

}
