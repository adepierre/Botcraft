#pragma once

#include "protocolCraft/Types/NBT/NBT.hpp"

#include <string>

namespace Botcraft
{
    short GetEnchantmentLvl(const ProtocolCraft::NBT& item_nbt, const std::string& enchantment_name);
}
