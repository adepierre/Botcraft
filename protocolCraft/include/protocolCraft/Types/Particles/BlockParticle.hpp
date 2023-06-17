#if PROTOCOL_VERSION > 392
#pragma once

#include "protocolCraft/Types/Particles/Particle.hpp"

namespace ProtocolCraft
{
    class BlockParticle : public Particle
    {
    public:
        BlockParticle();
        
        virtual ~BlockParticle();
        
        virtual std::string GetName() const override;
        
        virtual ParticleType GetType() const override;

        int GetState() const;

        void SetState(const int state_);
        
    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override;
        
        virtual void WriteImpl(WriteContainer &container) const override;
        
        virtual Json::Value SerializeImpl() const override;
        
    private:
        int state = 0;
    };
}
#endif
