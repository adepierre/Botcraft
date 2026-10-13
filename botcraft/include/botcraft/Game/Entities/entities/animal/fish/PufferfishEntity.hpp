#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/fish/AbstractFishEntity.hpp"

namespace Botcraft
{
    class PufferfishEntity : public AbstractFishEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("puff_state"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AbstractFishEntity::metadata_count + AbstractFishEntity::hierarchy_metadata_count;

    public:
        PufferfishEntity();
        virtual ~PufferfishEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetPuffState() const;

        void SetPuffState(const int puff_state);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
