#pragma once

#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#include <memory>
#include <string>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    enum class BrigadierPropertyType
    {
        None = -1,
        Bool,
        Float,
        Double,
        Integer,
        Long,
        String,
        Entity,
        GameProfile,
        BlockPos,
        ColumnPos,
        Vec3,
        Vec2,
        BlockState,
        BlockPredicate,
        ItemStack,
        ItemPredicate,
        Color,
        Component,
        Message,
        NbtCompoundTag,
        NbtTag,
        NbtPath,
        Objective,
        ObjectiveCriteria,
        Operation,
        Particle,
        Angle,
        Rotation,
        ScoreboardSlot,
        ScoreHolder,
        Swizzle,
        Team,
        ItemSlot,
        ResourceLocation,
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        MobEffect,
#endif
        Function,
        EntityAnchor,
        IntRange,
        FloatRange,
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        ItemEnchantment,
        EntitySummon,
#endif
        Dimension,
#if PROTOCOL_VERSION > 760 /* > 1.19.1/2 */
        Gamemode,
#endif
        Time,
        ResourceOrTag,
#if PROTOCOL_VERSION > 760 /* > 1.19.1/2 */
        ResourceOrTagKey,
#endif
        Resource,
#if PROTOCOL_VERSION > 760 /* > 1.19.1/2 */
        ResourceKey,
#endif
        TemplateMirror,
        TemplateRotation,
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        Heightmap,
#endif
        Uuid,
    };
#endif

    class BrigadierProperty : public NetworkType
    {
    public:
        virtual ~BrigadierProperty() override;

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        static std::shared_ptr<BrigadierProperty> CreateProperties(const Identifier& parser_identifier);
#else
        static std::shared_ptr<BrigadierProperty> CreateProperties(const BrigadierPropertyType parser_id);
#endif
    };
}
#endif
