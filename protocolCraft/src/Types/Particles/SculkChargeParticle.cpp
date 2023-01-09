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
    
    const nlohmann::json SculkChargeParticle::SerializeImpl() const
    {
        nlohmann::json output;

        output["roll"] = roll;

        return output;
    }
}
#endif
