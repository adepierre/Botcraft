#if PROTOCOL_VERSION > 758
#include "protocolCraft/Types/Particles/ShriekParticle.hpp"

namespace ProtocolCraft
{
    ShriekParticle::ShriekParticle()
    {
        
    }
    
    ShriekParticle::~ShriekParticle()
    {
        
    }
    
    std::string ShriekParticle::GetName() const
    {
        return "shriek";
    }
    
    ParticleType ShriekParticle::GetType() const
    {
        return ParticleType::Shriek;
    }

    const int ShriekParticle::GetDelay() const
    {
        return delay;
    }

    void ShriekParticle::SetDelay(const int delay_)
    {
        delay = delay_;
    }
    
    void ShriekParticle::ReadImpl(ReadIterator& iter, size_t& length)
    {
        delay = ReadData<VarInt>(iter, length);
    }
    
    void ShriekParticle::WriteImpl(WriteContainer& container) const
    {
        WriteData<VarInt>(delay, container);
    }
    
    const nlohmann::json ShriekParticle::SerializeImpl() const
    {
        nlohmann::json output;

        output["delay"] = delay;
        
        return output;
    }
}
#endif
