#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Particles/ColorParticleOptions.hpp"

namespace ProtocolCraft
{
    ColorParticleOptions::ColorParticleOptions()
    {

    }

    ColorParticleOptions::~ColorParticleOptions()
    {

    }

    int ColorParticleOptions::GetColor() const
    {
        return color;
    }

    void ColorParticleOptions::SetColor(const int color_)
    {
        color = color_;
    }

    void ColorParticleOptions::ReadImpl(ReadIterator& iter, size_t& length)
    {
        color = ReadData<int>(iter, length);
    }

    void ColorParticleOptions::WriteImpl(WriteContainer& container) const
    {
        WriteData<int>(color, container);
    }

    Json::Value ColorParticleOptions::SerializeImpl() const
    {
        Json::Value output;

        output["color"] = color;

        return output;
    }
}
#endif
