#if PROTOCOL_VERSION > 736
#include "botcraft/Game/Entities/entities/monster/piglin/AbstractPiglinEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, AbstractPiglinEntity::metadata_count> AbstractPiglinEntity::metadata_names{ {
        "data_immune_to_zombification",
    } };

    AbstractPiglinEntity::AbstractPiglinEntity()
    {
        // Initialize all metadata with default values
        SetDataImmuneToZombification(false);
    }

    AbstractPiglinEntity::~AbstractPiglinEntity()
    {

    }

    bool AbstractPiglinEntity::IsAbstractPiglin() const
    {
        return true;
    }


    ProtocolCraft::Json::Value AbstractPiglinEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_immune_to_zombification"] = GetDataImmuneToZombification();

        return output;
    }


    void AbstractPiglinEntity::SetMetadataValue(const int index, const std::any& value)
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

    bool AbstractPiglinEntity::GetDataImmuneToZombification() const
    {
        return std::any_cast<bool>(metadata.at("data_immune_to_zombification"));
    }


    void AbstractPiglinEntity::SetDataImmuneToZombification(const bool data_immune_to_zombification)
    {
        metadata["data_immune_to_zombification"] = data_immune_to_zombification;
    }

}
#endif
