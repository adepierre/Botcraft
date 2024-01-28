#pragma once

#if PROTOCOL_VERSION < 393 /* < 1.13 */
#include "botcraft/Game/Enums.hpp"
#else
#include <string>
#endif

namespace ProtocolCraft
{
    namespace NBT
    {
        class Value;
    }
}

namespace Botcraft::Utilities
{
#if PROTOCOL_VERSION < 393 /* < 1.13 */
    short GetEnchantmentLvl(const ProtocolCraft::NBT::Value& item_nbt, const Botcraft::EnchantmentID enchantment_id);
#else
    short GetEnchantmentLvl(const ProtocolCraft::NBT::Value& item_nbt, const std::string& enchantment_name);
#endif
    int GetDamageCount(const ProtocolCraft::NBT::Value& item_nbt);
}
