#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/equine/AbstractHorseEntity.hpp"

namespace Botcraft
{
    class CamelEntity : public AbstractHorseEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("dash"),
            std::string_view("last_pose_change_tick"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AbstractHorseEntity::metadata_count + AbstractHorseEntity::hierarchy_metadata_count;

    public:
        CamelEntity();
        virtual ~CamelEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        bool GetDash() const;
        long long int GetLastPoseChangeTick() const;

        void SetDash(const bool dash);
        void SetLastPoseChangeTick(const long long int last_pose_change_tick);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
