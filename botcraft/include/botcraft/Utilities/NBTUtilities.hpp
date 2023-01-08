#pragma once

#include <string>

namespace ProtocolCraft
{
    class NBT;
}

namespace Botcraft
{
    short GetEnchantmentLvl(const ProtocolCraft::NBT& item_nbt, const std::string& enchantment_name);
}
