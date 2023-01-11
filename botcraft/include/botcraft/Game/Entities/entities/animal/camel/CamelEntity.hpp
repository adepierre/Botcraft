#if PROTOCOL_VERSION > 760
#pragma once

#include "botcraft/Game/Entities/entities/animal/horse/AbstractHorseEntity.hpp"

namespace Botcraft
{
    class CamelEntity : public AbstractHorseEntity
    {
    protected:
        static constexpr int metadata_count = 2;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AbstractHorseEntity::metadata_count + AbstractHorseEntity::hierarchy_metadata_count;

    public:
        CamelEntity();
        virtual ~CamelEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        bool GetDash() const;
        long long int GetLastPoseChangeTick() const;

        void SetDash(const bool dash);
        void SetLastPoseChangeTick(const long long int last_pose_change_tick);

    };
}
#endif
