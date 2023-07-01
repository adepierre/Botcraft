#pragma once

#include <string>

namespace ProtocolCraft
{
    namespace NBT
    {
        class Value;
    }
}

namespace Botcraft::Utilities
{
    short GetEnchantmentLvl(const ProtocolCraft::NBT::Value& item_nbt, const std::string& enchantment_name);
}
