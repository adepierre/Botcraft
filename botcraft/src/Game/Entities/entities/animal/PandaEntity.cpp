#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/animal/PandaEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, PandaEntity::metadata_count> PandaEntity::metadata_names{ {
        "unhappy_counter",
        "sneeze_counter",
        "eat_counter",
        "main_gene_id",
        "hidden_gene_id",
        "data_id_flags",
    } };

    PandaEntity::PandaEntity()
    {
        // Initialize all metadata with default values
        SetUnhappyCounter(0);
        SetSneezeCounter(0);
        SetEatCounter(0);
        SetMainGeneId(0);
        SetHiddenGeneId(0);
        SetDataIdFlags(0);
    }

    PandaEntity::~PandaEntity()
    {

    }


    std::string PandaEntity::GetName() const
    {
        return "Panda";
    }

    EntityType PandaEntity::GetType() const
    {
        return EntityType::Panda;
    }

    double PandaEntity::GetWidth() const
    {
        return 1.3;
    }

    double PandaEntity::GetHeight() const
    {
        return 1.25;
    }


    std::string PandaEntity::GetClassName()
    {
        return "Panda";
    }

    EntityType PandaEntity::GetClassType()
    {
        return EntityType::Panda;
    }


    nlohmann::json PandaEntity::Serialize() const
    {
        nlohmann::json output = AnimalEntity::Serialize();

        output["metadata"]["unhappy_counter"] = GetUnhappyCounter();
        output["metadata"]["sneeze_counter"] = GetSneezeCounter();
        output["metadata"]["eat_counter"] = GetEatCounter();
        output["metadata"]["main_gene_id"] = GetMainGeneId();
        output["metadata"]["hidden_gene_id"] = GetHiddenGeneId();
        output["metadata"]["data_id_flags"] = GetDataIdFlags();

        return output;
    }


    void PandaEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int PandaEntity::GetUnhappyCounter() const
    {
        return std::any_cast<int>(metadata.at("unhappy_counter"));
    }

    int PandaEntity::GetSneezeCounter() const
    {
        return std::any_cast<int>(metadata.at("sneeze_counter"));
    }

    int PandaEntity::GetEatCounter() const
    {
        return std::any_cast<int>(metadata.at("eat_counter"));
    }

    char PandaEntity::GetMainGeneId() const
    {
        return std::any_cast<char>(metadata.at("main_gene_id"));
    }

    char PandaEntity::GetHiddenGeneId() const
    {
        return std::any_cast<char>(metadata.at("hidden_gene_id"));
    }

    char PandaEntity::GetDataIdFlags() const
    {
        return std::any_cast<char>(metadata.at("data_id_flags"));
    }


    void PandaEntity::SetUnhappyCounter(const int unhappy_counter)
    {
        metadata["unhappy_counter"] = unhappy_counter;
    }

    void PandaEntity::SetSneezeCounter(const int sneeze_counter)
    {
        metadata["sneeze_counter"] = sneeze_counter;
    }

    void PandaEntity::SetEatCounter(const int eat_counter)
    {
        metadata["eat_counter"] = eat_counter;
    }

    void PandaEntity::SetMainGeneId(const char main_gene_id)
    {
        metadata["main_gene_id"] = main_gene_id;
    }

    void PandaEntity::SetHiddenGeneId(const char hidden_gene_id)
    {
        metadata["hidden_gene_id"] = hidden_gene_id;
    }

    void PandaEntity::SetDataIdFlags(const char data_id_flags)
    {
        metadata["data_id_flags"] = data_id_flags;
    }

}
#endif
