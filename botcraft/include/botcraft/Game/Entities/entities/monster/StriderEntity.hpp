#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class StriderEntity : public AnimalEntity
    {
    protected:
        static constexpr int metadata_count = 3;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        StriderEntity();
        virtual ~StriderEntity();

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

        int GetDataBoostTime() const;
        bool GetDataSuffocating() const;
        bool GetDataSaddleId() const;

        void SetDataBoostTime(const int data_boost_time);
        void SetDataSuffocating(const bool data_suffocating);
        void SetDataSaddleId(const bool data_saddle_id);

    };
}
#endif
