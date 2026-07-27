#include "botcraft/Utilities/MathsUtilities.hpp"

#include <cmath>


#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
namespace
{
    constexpr float SIN_SCALE = 10430.378f; /* 65536 / 2 / pi but with less accuracy */
    constexpr float COS_OFFSET = 16384.0f;
    constexpr long long int SIN_MASK = 65535L;

    // If profiling shows a bottleneck, replace with the actual 65536 LUT
    float LUT(const int index)
    {
        return static_cast<float>(std::sin(static_cast<double>(index) * 3.141592653589793 * 2.0 / 65536.0));
    }
}

float SinLUT(const double d)
{
    return LUT(static_cast<int>(static_cast<float>(d) * SIN_SCALE) & SIN_MASK);
}

float CosLUT(const double d)
{
    return LUT(static_cast<int>(static_cast<float>(d) * SIN_SCALE + COS_OFFSET) & SIN_MASK);
}
#else
namespace
{
    constexpr double SIN_SCALE = 10430.378350470453; /* 65536 / 2 / pi */
    constexpr int COS_OFFSET = 16384;
    constexpr long long int SIN_MASK = 65535L;

    // If profiling shows a bottleneck, replace with the actual 65536 LUT
    float LUT(const int index)
    {
        return static_cast<float>(std::sin(static_cast<double>(index) / SIN_SCALE));
    }
}

float SinLUT(const double d)
{
    return LUT(static_cast<int>(static_cast<long long>(d * SIN_SCALE) & SIN_MASK));
}

float CosLUT(const double d)
{
    return LUT(static_cast<int>(static_cast<long long>(d * SIN_SCALE + COS_OFFSET) & SIN_MASK));
}
#endif
