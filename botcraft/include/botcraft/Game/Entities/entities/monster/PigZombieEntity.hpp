#if PROTOCOL_VERSION < 579 /* < 1.16 */
#pragma once

#include "botcraft/Game/Entities/entities/monster/ZombieEntity.hpp"

namespace Botcraft
{
    class PigZombieEntity : public ZombieEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = ZombieEntity::metadata_count + ZombieEntity::hierarchy_metadata_count;

    public:
        PigZombieEntity();
        virtual ~PigZombieEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

        // Attribute stuff
        // 49455a49-7ec5-45ba-b886-3b90b23a1718
        static constexpr std::array<unsigned char, 16> speed_modifier_attacking_uuid = { 0x49, 0x45, 0x5A, 0x49, 0x7E, 0xC5, 0x45, 0xBA, 0xB8, 0x86, 0x3B, 0x90, 0xB2, 0x3A, 0x17, 0x18 };

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
