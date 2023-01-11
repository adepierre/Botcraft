#if PROTOCOL_VERSION > 340
#pragma once

#include "botcraft/Game/Entities/entities/animal/AbstractFishEntity.hpp"

namespace Botcraft
{
    class PufferfishEntity : public AbstractFishEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AbstractFishEntity::metadata_count + AbstractFishEntity::hierarchy_metadata_count;

    public:
        PufferfishEntity();
        virtual ~PufferfishEntity();

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

        int GetPuffState() const;

        void SetPuffState(const int puff_state);

    };
}
#endif
