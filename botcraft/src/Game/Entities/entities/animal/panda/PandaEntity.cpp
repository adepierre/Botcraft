#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "botcraft/Game/Entities/entities/animal/panda/PandaEntity.hpp"

namespace Botcraft
{
    PandaEntity::PandaEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetUnhappyCounter(0);
        SetSneezeCounter(0);
        SetEatCounter(0);
        SetMainGeneId(0);
        SetHiddenGeneId(0);
        SetDataIdFlags(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.15) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 6.0) });
    }

    PandaEntity::~PandaEntity()
    {

    }


    std::string PandaEntity::GetName() const
    {
        return "panda";
    }

    EntityType PandaEntity::GetType() const
    {
        return EntityType::Panda;
    }


    std::string PandaEntity::GetClassName()
    {
        return "panda";
    }

    EntityType PandaEntity::GetClassType()
    {
        return EntityType::Panda;
    }


    ProtocolCraft::Json::Value PandaEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["unhappy_counter"] = GetUnhappyCounter();
        output["metadata"]["sneeze_counter"] = GetSneezeCounter();
        output["metadata"]["eat_counter"] = GetEatCounter();
        output["metadata"]["main_gene_id"] = GetMainGeneId();
        output["metadata"]["hidden_gene_id"] = GetHiddenGeneId();
        output["metadata"]["data_id_flags"] = GetDataIdFlags();

        output["attributes"]["attack_damage"] = GetAttributeAttackDamageValue();

        return output;
    }


    int PandaEntity::GetUnhappyCounter() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("unhappy_counter"));
    }

    int PandaEntity::GetSneezeCounter() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("sneeze_counter"));
    }

    int PandaEntity::GetEatCounter() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("eat_counter"));
    }

    char PandaEntity::GetMainGeneId() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("main_gene_id"));
    }

    char PandaEntity::GetHiddenGeneId() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("hidden_gene_id"));
    }

    char PandaEntity::GetDataIdFlags() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_flags"));
    }


    void PandaEntity::SetUnhappyCounter(const int unhappy_counter)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("unhappy_counter"), unhappy_counter);
    }

    void PandaEntity::SetSneezeCounter(const int sneeze_counter)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("sneeze_counter"), sneeze_counter);
    }

    void PandaEntity::SetEatCounter(const int eat_counter)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("eat_counter"), eat_counter);
    }

    void PandaEntity::SetMainGeneId(const char main_gene_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("main_gene_id"), main_gene_id);
    }

    void PandaEntity::SetHiddenGeneId(const char hidden_gene_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("hidden_gene_id"), hidden_gene_id);
    }

    void PandaEntity::SetDataIdFlags(const char data_id_flags)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_flags"), data_id_flags);
    }


    double PandaEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }


    double PandaEntity::GetWidthImpl() const
    {
        return 1.3;
    }

    double PandaEntity::GetHeightImpl() const
    {
        return 1.25;
    }

}
#endif
