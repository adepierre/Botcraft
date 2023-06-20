#pragma once

#include <vector>

namespace ProtocolCraft
{
    std::vector<unsigned char> ExtractGZip(std::vector<unsigned char>::const_iterator& iter, std::size_t& length);
}
