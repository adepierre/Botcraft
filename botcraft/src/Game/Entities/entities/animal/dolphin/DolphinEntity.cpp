#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "botcraft/Game/Entities/entities/animal/dolphin/DolphinEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, DolphinEntity::metadata_count> DolphinEntity::metadata_names{ {
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        "treasure_pos",
#endif
        "got_fish",
        "moistness_level",
    } };

    DolphinEntity::DolphinEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        SetTreasurePos(Position(0, 0, 0));
#endif
        SetGotFish(false);
        SetMoistnessLevel(2400);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 10.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 1.2) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 3.0) });
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
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        ProtocolCraft::Json::Value output = WaterAnimalEntity::Serialize();
#else
        ProtocolCraft::Json::Value output = AgeableWaterCreatureEntity::Serialize();
#endif

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        output["metadata"]["treasure_pos"] = GetTreasurePos().Serialize();
#endif
        output["metadata"]["got_fish"] = GetGotFish();
        output["metadata"]["moistness_level"] = GetMoistnessLevel();

        output["attributes"]["attack_damage"] = GetAttributeAttackDamageValue();

        return output;
    }


    void DolphinEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
            WaterAnimalEntity::SetMetadataValue(index, value);
#else
            AgeableWaterCreatureEntity::SetMetadataValue(index, value);
#endif
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    Position DolphinEntity::GetTreasurePos() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<Position>(metadata.at("treasure_pos"));
    }
#endif

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


#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    void DolphinEntity::SetTreasurePos(const Position& treasure_pos)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["treasure_pos"] = treasure_pos;
    }
#endif

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


    double DolphinEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }


    double DolphinEntity::GetWidthImpl() const
    {
        return 0.9;
    }

    double DolphinEntity::GetHeightImpl() const
    {
        return 0.6;
    }

}
#endif
