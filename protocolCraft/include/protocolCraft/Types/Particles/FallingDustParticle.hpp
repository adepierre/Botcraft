#pragma once

#include "protocolCraft/Types/Particles/Particle.hpp"

namespace ProtocolCraft
{
    class FallingDustParticle : public Particle
    {
    public:
        FallingDustParticle();
        
        virtual ~FallingDustParticle();
        
        virtual std::string GetName() const override;
        
        virtual ParticleType GetType() const override;

#if PROTOCOL_VERSION > 392
        int GetState() const;

        void SetState(const int state_);
#else
        int GetArgument1() const;
        
        void SetArgument1(const int argument1_);
#endif
        
    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override;
        
        virtual void WriteImpl(WriteContainer &container) const override;
        
        virtual const nlohmann::json SerializeImpl() const override;

    private:
#if PROTOCOL_VERSION > 392
        int state;
#else
        int argument1;
#endif
        
    };
}
