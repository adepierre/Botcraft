#pragma once

#include "botcraft/Game/Enums.hpp"

namespace ProtocolCraft
{
    class Slot;
}

namespace Botcraft::Utilities
{
    short GetEnchantmentLvl(const ProtocolCraft::Slot& item, const Botcraft::Enchantment enchantment);
    int GetDamageCount(const ProtocolCraft::Slot& item);
}
