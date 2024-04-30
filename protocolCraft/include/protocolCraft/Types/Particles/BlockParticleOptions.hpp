#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class BlockParticleOptions : public ParticleOptions
    {
    public:
        BlockParticleOptions();

        virtual ~BlockParticleOptions();

        int GetState() const;

        void SetState(const int state_);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
        virtual void WriteImpl(WriteContainer& container) const override;
        virtual Json::Value SerializeImpl() const override;
        
    private:
        int state = 0;
    };
}
