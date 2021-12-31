#if PROTOCOL_VERSION < 393
#include "protocolCraft/Types/Particles/BlockcrackParticle.hpp"

namespace ProtocolCraft
{
    BlockcrackParticle::BlockcrackParticle()
    {
        
    }
    
    BlockcrackParticle::~BlockcrackParticle()
    {
        
    }
    
    std::string BlockcrackParticle::GetName() const
    {
        return "blockcrack";
    }
    
    ParticleType BlockcrackParticle::GetType() const
    {
        return ParticleType::Blockcrack;
    }
    
    int BlockcrackParticle::GetArgument1() const
    {
        return argument1;
    }
    
    void BlockcrackParticle::SetArgument1(const int argument1_)
    {
        argument1 = argument1_;
    }
    
    void BlockcrackParticle::ReadImpl(ReadIterator& iter, size_t& length)
    {
        argument1 = ReadData<VarInt>(iter, length);
    }
    
    void BlockcrackParticle::WriteImpl(WriteContainer& container) const
    {
        WriteData<VarInt>(argument1, container);
    }
    
    const nlohmann::json BlockcrackParticle::SerializeImpl() const
    {
        nlohmann::json output;
        
        output["argument1"] = argument1;
        
        return output;
    }
}
#endif
