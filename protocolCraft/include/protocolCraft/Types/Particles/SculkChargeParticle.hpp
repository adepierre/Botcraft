#if PROTOCOL_VERSION > 758
#pragma once

#include "protocolCraft/Types/Particles/Particle.hpp"

namespace ProtocolCraft
{
    class SculkChargeParticle : public Particle
    {
    public:
        SculkChargeParticle();
        
        virtual ~SculkChargeParticle();
        
        virtual std::string GetName() const override;
        
        virtual ParticleType GetType() const override;

        float GetRoll() const;

        void SetRoll(const float roll_);
        
    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override;
        
        virtual void WriteImpl(WriteContainer &container) const override;
        
        virtual Json::Value SerializeImpl() const override;
        
    private:
        float roll = 0.0f;
    };
}
#endif
