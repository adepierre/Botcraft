#if PROTOCOL_VERSION > 392
#include "protocolCraft/Types/Particles/DustParticle.hpp"

namespace ProtocolCraft
{
    DustParticle::DustParticle()
    {
        
    }
    
    DustParticle::~DustParticle()
    {
        
    }
    
    std::string DustParticle::GetName() const
    {
        return "dust";
    }
    
    ParticleType DustParticle::GetType() const
    {
        return ParticleType::Dust;
    }

    float DustParticle::GetRed() const
    {
        return red;
    }

    float DustParticle::GetGreen() const
    {
        return green;
    }

    float DustParticle::GetBlue() const
    {
        return blue;
    }

    float DustParticle::GetScale() const
    {
        return scale;
    }

    void DustParticle::SetRed(const float red_)
    {
        red = red_;
    }

    void DustParticle::SetGreen(const float green_)
    {
        green = green_;
    }

    void DustParticle::SetBlue(const float blue_)
    {
        blue = blue_;
    }

    void DustParticle::SetScale(const float scale_)
    {
        scale = scale_;
    }
    
    void DustParticle::ReadImpl(ReadIterator& iter, size_t& length)
    {
        red = ReadData<float>(iter, length);
        green = ReadData<float>(iter, length);
        blue = ReadData<float>(iter, length);
        scale = ReadData<float>(iter, length);
    }
    
    void DustParticle::WriteImpl(WriteContainer& container) const
    {
        WriteData(red, container);
        WriteData(green, container);
        WriteData(blue, container);
        WriteData(scale, container);
    }
    
    Json::Value DustParticle::SerializeImpl() const
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
