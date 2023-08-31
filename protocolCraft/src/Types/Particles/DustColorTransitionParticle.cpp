#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
#include "protocolCraft/Types/Particles/DustColorTransitionParticle.hpp"

namespace ProtocolCraft
{
    DustColorTransitionParticle::DustColorTransitionParticle()
    {
        
    }
    
    DustColorTransitionParticle::~DustColorTransitionParticle()
    {
        
    }
    
    std::string DustColorTransitionParticle::GetName() const
    {
        return "dust_color_transition";
    }
    
    ParticleType DustColorTransitionParticle::GetType() const
    {
        return ParticleType::DustColorTransition;
    }

    float DustColorTransitionParticle::GetFromRed() const
    {
        return from_red;
    }

    float DustColorTransitionParticle::GetFromGreen() const
    {
        return from_green;
    }

    float DustColorTransitionParticle::GetFromBlue() const
    {
        return from_blue;
    }

    float DustColorTransitionParticle::GetScale() const
    {
        return scale;
    }

    float DustColorTransitionParticle::GetToRed() const
    {
        return to_red;
    }

    float DustColorTransitionParticle::GetToGreen() const
    {
        return to_green;
    }

    float DustColorTransitionParticle::GetToBlue() const
    {
        return to_blue;
    }

    void DustColorTransitionParticle::SetFromRed(const float from_red_)
    {
        from_red = from_red_;
    }

    void DustColorTransitionParticle::SetFromGreen(const float from_green_)
    {
        from_green = from_green_;
    }

    void DustColorTransitionParticle::SetFromBlue(const float from_blue_)
    {
        from_blue = from_blue_;
    }

    void DustColorTransitionParticle::SetScale(const float scale_)
    {
        scale = scale_;
    }

    void DustColorTransitionParticle::SetToRed(const float to_red_)
    {
        to_red = to_red_;
    }

    void DustColorTransitionParticle::SetToGreen(const float to_green_)
    {
        to_green = to_green_;
    }

    void DustColorTransitionParticle::SetToBlue(const float to_blue_)
    {
        to_blue = to_blue_;
    }
    
    void DustColorTransitionParticle::ReadImpl(ReadIterator& iter, size_t& length)
    {
        from_red = ReadData<float>(iter, length);
        from_green = ReadData<float>(iter, length);
        from_blue = ReadData<float>(iter, length);
        scale = ReadData<float>(iter, length);
        to_red = ReadData<float>(iter, length);
        to_green = ReadData<float>(iter, length);
        to_blue = ReadData<float>(iter, length);
    }
    
    void DustColorTransitionParticle::WriteImpl(WriteContainer& container) const
    {
        WriteData(from_red, container);
        WriteData(from_green, container);
        WriteData(from_blue, container);
        WriteData(scale, container);
        WriteData(to_red, container);
        WriteData(to_green, container);
        WriteData(to_blue, container);
    }
    
    Json::Value DustColorTransitionParticle::SerializeImpl() const
    {
        Json::Value output;

        output["from_red"] = from_red;
        output["from_green"] = from_green;
        output["from_blue"] = from_blue;
        output["scale"] = scale;
        output["to_red"] = to_red;
        output["to_green"] = to_green;
        output["to_blue"] = to_blue;

        return output;
    }
}
#endif
