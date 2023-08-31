#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "botcraft/Game/Entities/entities/animal/TurtleEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, TurtleEntity::metadata_count> TurtleEntity::metadata_names{ {
        "home_pos",
        "has_egg",
        "laying_egg",
        "travel_pos",
        "going_home",
        "travelling",
    } };

    TurtleEntity::TurtleEntity()
    {
        // Initialize all metadata with default values
        SetHomePos(Position(0, 0, 0));
        SetHasEgg(false);
        SetLayingEgg(false);
        SetTravelPos(Position(0, 0, 0));
        SetGoingHome(false);
        SetTravelling(false);
    }

    TurtleEntity::~TurtleEntity()
    {

    }


    std::string TurtleEntity::GetName() const
    {
        return "turtle";
    }

    EntityType TurtleEntity::GetType() const
    {
        return EntityType::Turtle;
    }

    double TurtleEntity::GetWidth() const
    {
        return 1.2;
    }

    double TurtleEntity::GetHeight() const
    {
        return 0.4;
    }


    std::string TurtleEntity::GetClassName()
    {
        return "turtle";
    }

    EntityType TurtleEntity::GetClassType()
    {
        return EntityType::Turtle;
    }


    ProtocolCraft::Json::Value TurtleEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["home_pos"] = GetHomePos().Serialize();
        output["metadata"]["has_egg"] = GetHasEgg();
        output["metadata"]["laying_egg"] = GetLayingEgg();
        output["metadata"]["travel_pos"] = GetTravelPos().Serialize();
        output["metadata"]["going_home"] = GetGoingHome();
        output["metadata"]["travelling"] = GetTravelling();

        return output;
    }


    void TurtleEntity::SetMetadataValue(const int index, const std::any& value)
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

    const Position& TurtleEntity::GetHomePos() const
    {
        return std::any_cast<const Position&>(metadata.at("home_pos"));
    }

    bool TurtleEntity::GetHasEgg() const
    {
        return std::any_cast<bool>(metadata.at("has_egg"));
    }

    bool TurtleEntity::GetLayingEgg() const
    {
        return std::any_cast<bool>(metadata.at("laying_egg"));
    }

    const Position& TurtleEntity::GetTravelPos() const
    {
        return std::any_cast<const Position&>(metadata.at("travel_pos"));
    }

    bool TurtleEntity::GetGoingHome() const
    {
        return std::any_cast<bool>(metadata.at("going_home"));
    }

    bool TurtleEntity::GetTravelling() const
    {
        return std::any_cast<bool>(metadata.at("travelling"));
    }


    void TurtleEntity::SetHomePos(const Position& home_pos)
    {
        metadata["home_pos"] = home_pos;
    }

    void TurtleEntity::SetHasEgg(const bool has_egg)
    {
        metadata["has_egg"] = has_egg;
    }

    void TurtleEntity::SetLayingEgg(const bool laying_egg)
    {
        metadata["laying_egg"] = laying_egg;
    }

    void TurtleEntity::SetTravelPos(const Position& travel_pos)
    {
        metadata["travel_pos"] = travel_pos;
    }

    void TurtleEntity::SetGoingHome(const bool going_home)
    {
        metadata["going_home"] = going_home;
    }

    void TurtleEntity::SetTravelling(const bool travelling)
    {
        metadata["travelling"] = travelling;
    }

}
#endif
