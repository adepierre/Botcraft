#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
#include "protocolCraft/Types/Particles/DustParticleOptions.hpp"

namespace ProtocolCraft
{
    DustParticleOptions::DustParticleOptions()
    {

    }

    DustParticleOptions::~DustParticleOptions()
    {

    }

    float DustParticleOptions::GetRed() const
    {
        return red;
    }

    float DustParticleOptions::GetGreen() const
    {
        return green;
    }

    float DustParticleOptions::GetBlue() const
    {
        return blue;
    }

    float DustParticleOptions::GetScale() const
    {
        return scale;
    }

    void DustParticleOptions::SetRed(const float red_)
    {
        red = red_;
    }

    void DustParticleOptions::SetGreen(const float green_)
    {
        green = green_;
    }

    void DustParticleOptions::SetBlue(const float blue_)
    {
        blue = blue_;
    }

    void DustParticleOptions::SetScale(const float scale_)
    {
        scale = scale_;
    }

    void DustParticleOptions::ReadImpl(ReadIterator& iter, size_t& length)
    {
        red = ReadData<float>(iter, length);
        green = ReadData<float>(iter, length);
        blue = ReadData<float>(iter, length);
        scale = ReadData<float>(iter, length);
    }

    void DustParticleOptions::WriteImpl(WriteContainer& container) const
    {
        WriteData(red, container);
        WriteData(green, container);
        WriteData(blue, container);
        WriteData(scale, container);
    }

    Json::Value DustParticleOptions::SerializeImpl() const
    {
        Json::Value output;

        output["red"] = red;
        output["green"] = green;
        output["blue"] = blue;
        output["scale"] = scale;

        return output;
    }
}
#endif
