#if PROTOCOL_VERSION < 393
#include "protocolCraft/Types/Particles/BlockdustParticle.hpp"

namespace ProtocolCraft
{
    BlockdustParticle::BlockdustParticle()
    {
        
    }
    
    BlockdustParticle::~BlockdustParticle()
    {
        
    }
    
    std::string BlockdustParticle::GetName() const
    {
        return "blockdust";
    }
    
    ParticleType BlockdustParticle::GetType() const
    {
        return ParticleType::Blockdust;
    }
    
    int BlockdustParticle::GetArgument1() const
    {
        return argument1;
    }
    
    void BlockdustParticle::SetArgument1(const int argument1_)
    {
        argument1 = argument1_;
    }
    
    void BlockdustParticle::ReadImpl(ReadIterator& iter, size_t& length)
    {
        argument1 = ReadData<VarInt>(iter, length);
    }
    
    void BlockdustParticle::WriteImpl(WriteContainer& container) const
    {
        WriteData<VarInt>(argument1, container);
    }
    
    const nlohmann::json BlockdustParticle::SerializeImpl() const
    {
        nlohmann::json output;
        
        output["argument1"] = argument1;
        
        return output;
    }
}
#endif
