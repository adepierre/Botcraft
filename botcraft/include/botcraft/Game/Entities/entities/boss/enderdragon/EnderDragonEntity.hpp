#pragma once

#include "botcraft/Game/Entities/entities/MobEntity.hpp"

namespace Botcraft
{
    class EnderDragonEntity : public MobEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_phase"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = MobEntity::metadata_count + MobEntity::hierarchy_metadata_count;

    public:
        EnderDragonEntity();
        virtual ~EnderDragonEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetDataPhase() const;

        void SetDataPhase(const int data_phase);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
