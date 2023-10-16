#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "botcraft/Game/Entities/entities/animal/DolphinEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, DolphinEntity::metadata_count> DolphinEntity::metadata_names{ {
        "treasure_pos",
        "got_fish",
        "moistness_level",
    } };

    DolphinEntity::DolphinEntity()
    {
        // Initialize all metadata with default values
        SetTreasurePos(Position(0, 0, 0));
        SetGotFish(false);
        SetMoistnessLevel(2400);
    }

    DolphinEntity::~DolphinEntity()
    {

    }


    std::string DolphinEntity::GetName() const
    {
        return "dolphin";
    }

    EntityType DolphinEntity::GetType() const
    {
        return EntityType::Dolphin;
    }

    double DolphinEntity::GetWidth() const
    {
        return 0.9;
    }

    double DolphinEntity::GetHeight() const
    {
        return 0.6;
    }


    std::string DolphinEntity::GetClassName()
    {
        return "dolphin";
    }

    EntityType DolphinEntity::GetClassType()
    {
        return EntityType::Dolphin;
    }


    ProtocolCraft::Json::Value DolphinEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = WaterAnimalEntity::Serialize();

        output["metadata"]["treasure_pos"] = GetTreasurePos().Serialize();
        output["metadata"]["got_fish"] = GetGotFish();
        output["metadata"]["moistness_level"] = GetMoistnessLevel();

        return output;
    }


    void DolphinEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            WaterAnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    const Position& DolphinEntity::GetTreasurePos() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<const Position&>(metadata.at("treasure_pos"));
    }

    bool DolphinEntity::GetGotFish() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("got_fish"));
    }

    int DolphinEntity::GetMoistnessLevel() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("moistness_level"));
    }


    void DolphinEntity::SetTreasurePos(const Position& treasure_pos)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["treasure_pos"] = treasure_pos;
    }

    void DolphinEntity::SetGotFish(const bool got_fish)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["got_fish"] = got_fish;
    }

    void DolphinEntity::SetMoistnessLevel(const int moistness_level)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["moistness_level"] = moistness_level;
    }

}
#endif
