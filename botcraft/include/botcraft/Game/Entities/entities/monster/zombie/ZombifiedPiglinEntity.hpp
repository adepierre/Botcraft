#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#pragma once

#include "botcraft/Game/Entities/entities/monster/zombie/ZombieEntity.hpp"

namespace Botcraft
{
    class ZombifiedPiglinEntity : public ZombieEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = ZombieEntity::metadata_count + ZombieEntity::hierarchy_metadata_count;

    public:
        ZombifiedPiglinEntity();
        virtual ~ZombifiedPiglinEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

        // Attribute stuff
#if PROTOCOL_VERSION < 767 /* < 1.21 */
        // 49455a49-7ec5-45ba-b886-3b90b23a1718
        static constexpr std::array<unsigned char, 16> speed_modifier_attacking_key= { 0x49, 0x45, 0x5A, 0x49, 0x7E, 0xC5, 0x45, 0xBA, 0xB8, 0x86, 0x3B, 0x90, 0xB2, 0x3A, 0x17, 0x18 };
#else
        inline static const std::string speed_modifier_attacking_key = "minecraft:attacking";
#endif


    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
