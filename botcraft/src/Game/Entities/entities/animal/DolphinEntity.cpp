#if PROTOCOL_VERSION > 340
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
        return "Dolphin";
    }

    EntityType DolphinEntity::GetType() const
    {
        return EntityType::Dolphin;
    }

    AABB DolphinEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
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
        return "Dolphin";
    }

    EntityType DolphinEntity::GetClassType()
    {
        return EntityType::Dolphin;
    }


    nlohmann::json DolphinEntity::Serialize() const
    {
        nlohmann::json output = WaterAnimalEntity::Serialize();

        output["treasure_pos"] = GetTreasurePos().Serialize();
        output["got_fish"] = GetGotFish();
        output["moistness_level"] = GetMoistnessLevel();

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
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    const Position& DolphinEntity::GetTreasurePos() const
    {
        return std::any_cast<const Position&>(metadata.at("treasure_pos"));
    }

    bool DolphinEntity::GetGotFish() const
    {
        return std::any_cast<bool>(metadata.at("got_fish"));
    }

    int DolphinEntity::GetMoistnessLevel() const
    {
        return std::any_cast<int>(metadata.at("moistness_level"));
    }


    void DolphinEntity::SetTreasurePos(const Position& treasure_pos)
    {
        metadata["treasure_pos"] = treasure_pos;
    }

    void DolphinEntity::SetGotFish(const bool got_fish)
    {
        metadata["got_fish"] = got_fish;
    }

    void DolphinEntity::SetMoistnessLevel(const int moistness_level)
    {
        metadata["moistness_level"] = moistness_level;
    }

}
#endif
