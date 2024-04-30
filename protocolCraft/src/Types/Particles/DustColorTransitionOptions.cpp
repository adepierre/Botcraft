#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Types/Particles/DustColorTransitionOptions.hpp"

namespace ProtocolCraft
{
    DustColorTransitionOptions::DustColorTransitionOptions()
    {
        
    }
    
    DustColorTransitionOptions::~DustColorTransitionOptions()
    {
        
    }


    float DustColorTransitionOptions::GetFromRed() const
    {
        return from_red;
    }

    float DustColorTransitionOptions::GetFromGreen() const
    {
        return from_green;
    }

    float DustColorTransitionOptions::GetFromBlue() const
    {
        return from_blue;
    }

    float DustColorTransitionOptions::GetScale() const
    {
        return scale;
    }

    float DustColorTransitionOptions::GetToRed() const
    {
        return to_red;
    }

    float DustColorTransitionOptions::GetToGreen() const
    {
        return to_green;
    }

    float DustColorTransitionOptions::GetToBlue() const
    {
        return to_blue;
    }

    void DustColorTransitionOptions::SetFromRed(const float from_red_)
    {
        from_red = from_red_;
    }

    void DustColorTransitionOptions::SetFromGreen(const float from_green_)
    {
        from_green = from_green_;
    }

    void DustColorTransitionOptions::SetFromBlue(const float from_blue_)
    {
        from_blue = from_blue_;
    }

    void DustColorTransitionOptions::SetScale(const float scale_)
    {
        scale = scale_;
    }

    void DustColorTransitionOptions::SetToRed(const float to_red_)
    {
        to_red = to_red_;
    }

    void DustColorTransitionOptions::SetToGreen(const float to_green_)
    {
        to_green = to_green_;
    }

    void DustColorTransitionOptions::SetToBlue(const float to_blue_)
    {
        to_blue = to_blue_;
    }
    
    void DustColorTransitionOptions::ReadImpl(ReadIterator& iter, size_t& length)
    {
        from_red = ReadData<float>(iter, length);
        from_green = ReadData<float>(iter, length);
        from_blue = ReadData<float>(iter, length);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        scale = ReadData<float>(iter, length);
#endif
        to_red = ReadData<float>(iter, length);
        to_green = ReadData<float>(iter, length);
        to_blue = ReadData<float>(iter, length);
#if PROTOCOL_VERSION > 765 /* > 1.20.4> */
        scale = ReadData<float>(iter, length);
#endif
    }
    
    void DustColorTransitionOptions::WriteImpl(WriteContainer& container) const
    {
        WriteData(from_red, container);
        WriteData(from_green, container);
        WriteData(from_blue, container);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        WriteData(scale, container);
#endif
        WriteData(to_red, container);
        WriteData(to_green, container);
        WriteData(to_blue, container);
#if PROTOCOL_VERSION > 765 /* > 1.20.4> */
        WriteData(scale, container);
#endif
    }
    
    Json::Value DustColorTransitionOptions::SerializeImpl() const
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
