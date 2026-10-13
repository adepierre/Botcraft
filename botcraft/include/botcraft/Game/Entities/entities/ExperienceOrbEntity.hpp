#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"

namespace Botcraft
{
    class ExperienceOrbEntity : public Entity
    {
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_value"),
        };
#endif
    protected:
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        static constexpr int metadata_count = 0;
#else
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
#endif
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        ExperienceOrbEntity();
        virtual ~ExperienceOrbEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetDataValue() const;

        void SetDataValue(const int data_value);
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
