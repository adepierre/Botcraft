#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "botcraft/Game/Entities/entities/monster/skeleton/AbstractSkeletonEntity.hpp"

namespace Botcraft
{
    class BoggedEntity : public AbstractSkeletonEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_sheared"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AbstractSkeletonEntity::metadata_count + AbstractSkeletonEntity::hierarchy_metadata_count;

    public:
        BoggedEntity();
        virtual ~BoggedEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        bool GetDataSheared() const;

        void SetDataSheared(const bool data_sheared);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
