#pragma once

#include "botcraft/Game/Enums.hpp"

#include <string_view>

namespace ProtocolCraft
{
    class Slot;
}

namespace Botcraft::Utilities
{
    std::string_view EnchantmentToString(const Botcraft::Enchantment enchantment);
    short GetEnchantmentLvl(const ProtocolCraft::Slot& item, const Botcraft::Enchantment enchantment);
    int GetDamageCount(const ProtocolCraft::Slot& item);
}
