#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/golem/AbstractGolemEntity.hpp"

namespace Botcraft
{
    class CopperGolemEntity : public AbstractGolemEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("copper_golem_state"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AbstractGolemEntity::metadata_count + AbstractGolemEntity::hierarchy_metadata_count;

    public:
        CopperGolemEntity();
        virtual ~CopperGolemEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetCopperGolemState() const;

        void SetCopperGolemState(const int copper_golem_state);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
