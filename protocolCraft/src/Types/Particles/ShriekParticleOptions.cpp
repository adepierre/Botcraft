#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/Particles/ShriekParticleOptions.hpp"

namespace ProtocolCraft
{
    ShriekParticleOptions::ShriekParticleOptions()
    {
        
    }
    
    ShriekParticleOptions::~ShriekParticleOptions()
    {
        
    }

    int ShriekParticleOptions::GetDelay() const
    {
        return delay;
    }

    void ShriekParticleOptions::SetDelay(const int delay_)
    {
        delay = delay_;
    }
    
    void ShriekParticleOptions::ReadImpl(ReadIterator& iter, size_t& length)
    {
        delay = ReadData<VarInt>(iter, length);
    }
    
    void ShriekParticleOptions::WriteImpl(WriteContainer& container) const
    {
        WriteData<VarInt>(delay, container);
    }
    
    Json::Value ShriekParticleOptions::SerializeImpl() const
    {
        Json::Value output;

        output["delay"] = delay;
        
        return output;
    }
}
#endif
