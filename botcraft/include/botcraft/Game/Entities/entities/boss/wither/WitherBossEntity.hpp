#pragma once

#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"

namespace Botcraft
{
    class WitherBossEntity : public MonsterEntity
    {
    protected:
        static constexpr int metadata_count = 4;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = MonsterEntity::metadata_count + MonsterEntity::hierarchy_metadata_count;

    public:
        WitherBossEntity();
        virtual ~WitherBossEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual nlohmann::json Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataTargetA() const;
        int GetDataTargetB() const;
        int GetDataTargetC() const;
        int GetDataIdInv() const;

        void SetDataTargetA(const int data_target_a);
        void SetDataTargetB(const int data_target_b);
        void SetDataTargetC(const int data_target_c);
        void SetDataIdInv(const int data_id_inv);

    };
}
