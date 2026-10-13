#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class TurtleEntity : public AnimalEntity
    {
    private:
        static constexpr std::array metadata_names{
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
            std::string_view("home_pos"),
#endif
            std::string_view("has_egg"),
            std::string_view("laying_egg"),
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
            std::string_view("travel_pos"),
            std::string_view("going_home"),
            std::string_view("travelling"),
#endif
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        TurtleEntity();
        virtual ~TurtleEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        Position GetHomePos() const;
#endif
        bool GetHasEgg() const;
        bool GetLayingEgg() const;
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        Position GetTravelPos() const;
        bool GetGoingHome() const;
        bool GetTravelling() const;
#endif

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        void SetHomePos(const Position& home_pos);
#endif
        void SetHasEgg(const bool has_egg);
        void SetLayingEgg(const bool laying_egg);
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        void SetTravelPos(const Position& travel_pos);
        void SetGoingHome(const bool going_home);
        void SetTravelling(const bool travelling);
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
