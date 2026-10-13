#pragma once

#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"

namespace Botcraft
{
    class WitherBossEntity : public MonsterEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_target_a"),
            std::string_view("data_target_b"),
            std::string_view("data_target_c"),
            std::string_view("data_id_inv"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = MonsterEntity::metadata_count + MonsterEntity::hierarchy_metadata_count;

    public:
        WitherBossEntity();
        virtual ~WitherBossEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetDataTargetA() const;
        int GetDataTargetB() const;
        int GetDataTargetC() const;
        int GetDataIdInv() const;

        void SetDataTargetA(const int data_target_a);
        void SetDataTargetB(const int data_target_b);
        void SetDataTargetC(const int data_target_c);
        void SetDataIdInv(const int data_id_inv);

        // Attribute stuff
        double GetAttributeFlyingSpeedValue() const;

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
