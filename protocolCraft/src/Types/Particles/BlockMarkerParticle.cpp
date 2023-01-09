#if PROTOCOL_VERSION > 756

#include "protocolCraft/Types/Particles/BlockMarkerParticle.hpp"

namespace ProtocolCraft
{
    BlockMarkerParticle::BlockMarkerParticle()
    {
        
    }
    
    BlockMarkerParticle::~BlockMarkerParticle()
    {
        
    }
    
    std::string BlockMarkerParticle::GetName() const
    {
        return "block_marker";
    }
    
    ParticleType BlockMarkerParticle::GetType() const
    {
        return ParticleType::BlockMarker;
    }

    int BlockMarkerParticle::GetState() const
    {
        return state;
    }

    void BlockMarkerParticle::SetState(const int state_)
    {
        state = state_;
    }
    
    void BlockMarkerParticle::ReadImpl(ReadIterator& iter, size_t& length)
    {
        state = ReadData<VarInt>(iter, length);
    }
    
    void BlockMarkerParticle::WriteImpl(WriteContainer& container) const
    {
        WriteData<VarInt>(state, container);
    }
    
    Json::Value BlockMarkerParticle::SerializeImpl() const
    {
        Json::Value output;

        output["state"] = state;

        return output;
    }
}
#endif
