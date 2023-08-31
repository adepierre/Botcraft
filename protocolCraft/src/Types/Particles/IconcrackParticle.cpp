#if PROTOCOL_VERSION < 393 /* < 1.13 */
#include "protocolCraft/Types/Particles/IconcrackParticle.hpp"

namespace ProtocolCraft
{
    IconcrackParticle::IconcrackParticle()
    {
        
    }
    
    IconcrackParticle::~IconcrackParticle()
    {
        
    }
    
    std::string IconcrackParticle::GetName() const
    {
        return "iconcrack";
    }
    
    ParticleType IconcrackParticle::GetType() const
    {
        return ParticleType::Iconcrack;
    }
    
    int IconcrackParticle::GetArgument1() const
    {
        return argument1;
    }
    
    int IconcrackParticle::GetArgument2() const
    {
        return argument2;
    }
    
    void IconcrackParticle::SetArgument1(const int argument1_)
    {
        argument1 = argument1_;
    }
    
    void IconcrackParticle::SetArgument2(const int argument2_)
    {
        argument2 = argument2_;
    }
    
    void IconcrackParticle::ReadImpl(ReadIterator& iter, size_t& length)
    {
        argument1 = ReadData<VarInt>(iter, length);
        argument2 = ReadData<VarInt>(iter, length);
    }
    
    void IconcrackParticle::WriteImpl(WriteContainer& container) const
    {
        WriteData<VarInt>(argument1, container);
        WriteData<VarInt>(argument2, container);
    }
    
    Json::Value IconcrackParticle::SerializeImpl() const
    {
        Json::Value output;
        
        output["argument1"] = argument1;
        output["argument2"] = argument2;
        
        return output;
    }
}
#endif
