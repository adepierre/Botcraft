#include "protocolCraft/Types/Particles/BlockParticleOptions.hpp"

namespace ProtocolCraft
{
    BlockParticleOptions::BlockParticleOptions()
    {

    }

    BlockParticleOptions::~BlockParticleOptions()
    {

    }

    int BlockParticleOptions::GetState() const
    {
        return state;
    }

    void BlockParticleOptions::SetState(const int state_)
    {
        state = state_;
    }

    void BlockParticleOptions::ReadImpl(ReadIterator& iter, size_t& length)
    {
        state = ReadData<VarInt>(iter, length);
    }

    void BlockParticleOptions::WriteImpl(WriteContainer& container) const
    {
        WriteData<VarInt>(state, container);
    }

    Json::Value BlockParticleOptions::SerializeImpl() const
    {
        Json::Value output;

        output["state"] = state;

        return output;
    }
}
