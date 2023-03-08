#pragma once

#if PROTOCOL_VERSION > 344
#include <memory>
#include <string>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
#if PROTOCOL_VERSION > 758
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
#if PROTOCOL_VERSION < 761
        MobEffect,
#endif
        Function,
        EntityAnchor,
        IntRange,
        FloatRange,
#if PROTOCOL_VERSION < 761
        ItemEnchantment,
        EntitySummon,
#endif
        Dimension,
#if PROTOCOL_VERSION > 760
        Gamemode,
#endif
        Time,
        ResourceOrTag,
#if PROTOCOL_VERSION > 760
        ResourceOrTagKey,
#endif
        Resource,
#if PROTOCOL_VERSION > 760
        ResourceKey,
#endif
        TemplateMirror,
        TemplateRotation,
        Uuid,
    };
#endif

    class BrigadierProperty : public NetworkType
    {
    public:
        virtual ~BrigadierProperty() override;

#if PROTOCOL_VERSION < 759
        static std::shared_ptr<BrigadierProperty> CreateProperties(const Identifier& parser_identifier);
#else
        static std::shared_ptr<BrigadierProperty> CreateProperties(const BrigadierPropertyType parser_id);
#endif
    };
}
#endif
