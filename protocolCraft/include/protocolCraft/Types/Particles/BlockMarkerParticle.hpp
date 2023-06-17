#if PROTOCOL_VERSION > 756
#pragma once

#include "protocolCraft/Types/Particles/Particle.hpp"

namespace ProtocolCraft
{
    class BlockMarkerParticle : public Particle
    {
    public:
        BlockMarkerParticle();
        
        virtual ~BlockMarkerParticle();
        
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
