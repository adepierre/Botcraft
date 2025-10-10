#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/AbstractGolemEntity.hpp"

namespace Botcraft
{
    class CopperGolemEntity : public AbstractGolemEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
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
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetCopperGolemState() const;

        void SetCopperGolemState(const int copper_golem_state);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
