#if PROTOCOL_VERSION > 758
#include "protocolCraft/Types/Particles/SculkChargeParticle.hpp"

namespace ProtocolCraft
{
    SculkChargeParticle::SculkChargeParticle()
    {
        
    }
    
    SculkChargeParticle::~SculkChargeParticle()
    {
        
    }
    
    std::string SculkChargeParticle::GetName() const
    {
        return "sculk_charge";
    }
    
    ParticleType SculkChargeParticle::GetType() const
    {
        return ParticleType::SculkCharge;
    }

    float SculkChargeParticle::GetRoll() const
    {
        return roll;
    }
    
    void SculkChargeParticle::SetRoll(const float roll_)
    {
        roll = roll_;
    }

    void SculkChargeParticle::ReadImpl(ReadIterator& iter, size_t& length)
    {
        roll = ReadData<float>(iter, length);
    }
    
    void SculkChargeParticle::WriteImpl(WriteContainer& container) const
    {
        WriteData<float>(roll, container);
    }
    
    Json::Value SculkChargeParticle::SerializeImpl() const
    {
        Json::Value output;

        output["roll"] = roll;

        return output;
    }
}
#endif
