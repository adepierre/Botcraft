#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "botcraft/Game/Entities/entities/animal/turtle/TurtleEntity.hpp"

namespace Botcraft
{
    TurtleEntity::TurtleEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        SetHomePos(Position(0, 0, 0));
#endif
        SetHasEgg(false);
        SetLayingEgg(false);
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        SetTravelPos(Position(0, 0, 0));
        SetGoingHome(false);
        SetTravelling(false);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 30.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.25) });
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        attributes.insert({ EntityAttribute::Type::StepHeight, EntityAttribute(EntityAttribute::Type::StepHeight, 1.0) });
#endif
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

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        output["metadata"]["home_pos"] = GetHomePos().Serialize();
#endif
        output["metadata"]["has_egg"] = GetHasEgg();
        output["metadata"]["laying_egg"] = GetLayingEgg();
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        output["metadata"]["travel_pos"] = GetTravelPos().Serialize();
        output["metadata"]["going_home"] = GetGoingHome();
        output["metadata"]["travelling"] = GetTravelling();
#endif

        return output;
    }


#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    Position TurtleEntity::GetHomePos() const
    {
        return GetMetadata<Position>(BOTCRAFT_ENTITY_METADATA_INDEX("home_pos"));
    }
#endif

    bool TurtleEntity::GetHasEgg() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("has_egg"));
    }

    bool TurtleEntity::GetLayingEgg() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("laying_egg"));
    }

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    Position TurtleEntity::GetTravelPos() const
    {
        return GetMetadata<Position>(BOTCRAFT_ENTITY_METADATA_INDEX("travel_pos"));
    }

    bool TurtleEntity::GetGoingHome() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("going_home"));
    }

    bool TurtleEntity::GetTravelling() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("travelling"));
    }
#endif


#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    void TurtleEntity::SetHomePos(const Position& home_pos)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("home_pos"), home_pos);
    }
#endif

    void TurtleEntity::SetHasEgg(const bool has_egg)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("has_egg"), has_egg);
    }

    void TurtleEntity::SetLayingEgg(const bool laying_egg)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("laying_egg"), laying_egg);
    }

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    void TurtleEntity::SetTravelPos(const Position& travel_pos)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("travel_pos"), travel_pos);
    }

    void TurtleEntity::SetGoingHome(const bool going_home)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("going_home"), going_home);
    }

    void TurtleEntity::SetTravelling(const bool travelling)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("travelling"), travelling);
    }
#endif


    double TurtleEntity::GetWidthImpl() const
    {
        return 1.2;
    }

    double TurtleEntity::GetHeightImpl() const
    {
        return 0.4;
    }

}
#endif
