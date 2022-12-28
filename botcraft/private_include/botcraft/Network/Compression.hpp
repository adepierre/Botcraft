#pragma once

#include <vector>

namespace Botcraft
{
#ifdef USE_COMPRESSION
    std::vector<unsigned char> Compress(const std::vector<unsigned char> &raw);
    std::vector<unsigned char> Decompress(const std::vector<unsigned char> &compressed, const int start = 0);
#endif
} // Botcraft
