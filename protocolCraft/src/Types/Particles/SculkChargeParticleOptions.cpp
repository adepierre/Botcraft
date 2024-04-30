#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/Particles/SculkChargeParticleOptions.hpp"

namespace ProtocolCraft
{
    SculkChargeParticleOptions::SculkChargeParticleOptions()
    {
        
    }
    
    SculkChargeParticleOptions::~SculkChargeParticleOptions()
    {
        
    }

    float SculkChargeParticleOptions::GetRoll() const
    {
        return roll;
    }
    
    void SculkChargeParticleOptions::SetRoll(const float roll_)
    {
        roll = roll_;
    }

    void SculkChargeParticleOptions::ReadImpl(ReadIterator& iter, size_t& length)
    {
        roll = ReadData<float>(iter, length);
    }
    
    void SculkChargeParticleOptions::WriteImpl(WriteContainer& container) const
    {
        WriteData<float>(roll, container);
    }

    Json::Value SculkChargeParticleOptions::SerializeImpl() const
    {
        Json::Value output;

        output["roll"] = roll;

        return output;
    }
}
#endif
