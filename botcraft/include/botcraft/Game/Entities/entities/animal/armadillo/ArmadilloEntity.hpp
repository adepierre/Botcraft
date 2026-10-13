#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class ArmadilloEntity : public AnimalEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("armadillo_state"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        ArmadilloEntity();
        virtual ~ArmadilloEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetArmadilloState() const;

        void SetArmadilloState(const int armadillo_state);

        // Attribute stuff

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
