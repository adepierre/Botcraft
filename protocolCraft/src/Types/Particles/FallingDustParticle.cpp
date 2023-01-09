#include "protocolCraft/Types/Particles/FallingDustParticle.hpp"

namespace ProtocolCraft
{
    FallingDustParticle::FallingDustParticle()
    {
        
    }
    
    FallingDustParticle::~FallingDustParticle()
    {
        
    }
    
    std::string FallingDustParticle::GetName() const
    {
#if PROTOCOL_VERSION > 392
        return "falling_dust";
#else
        return "fallingdust";
#endif
    }
    
    ParticleType FallingDustParticle::GetType() const
    {
        return ParticleType::FallingDust;
    }

#if PROTOCOL_VERSION > 392
    int FallingDustParticle::GetState() const
    {
        return state;
    }

    void FallingDustParticle::SetState(const int state_)
    {
        state = state_;
    }
#else
    int FallingDustParticle::GetArgument1() const
    {
        return argument1;
    }
    
    void FallingDustParticle::SetArgument1(const int argument1_)
    {
        argument1 = argument1_;
    }
#endif
    
    void FallingDustParticle::ReadImpl(ReadIterator& iter, size_t& length)
    {
#if PROTOCOL_VERSION > 392
        state = ReadData<VarInt>(iter, length);
#else
        argument1 = ReadData<VarInt>(iter, length);
#endif

    }
    
    void FallingDustParticle::WriteImpl(WriteContainer& container) const
    {
#if PROTOCOL_VERSION > 392
        WriteData<VarInt>(state, container);
#else
        WriteData<VarInt>(argument1, container);
#endif
    }
    
    Json::Value FallingDustParticle::SerializeImpl() const
    {
        Json::Value output;

#if PROTOCOL_VERSION > 392
        output["state"] = state;
#else
        output["argument1"] = argument1;
#endif

        return output;
    }
}
