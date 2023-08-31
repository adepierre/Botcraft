#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/Types/Particles/Particle.hpp"

namespace ProtocolCraft
{
    class ShriekParticle : public Particle
    {
    public:
        ShriekParticle();
        
        virtual ~ShriekParticle();
        
        virtual std::string GetName() const override;
        
        virtual ParticleType GetType() const override;

        int GetDelay() const;

        void SetDelay(const int delay_);
        
    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override;
        
        virtual void WriteImpl(WriteContainer &container) const override;
        
        virtual Json::Value SerializeImpl() const override;
        
    private:
        int delay = 0;
    };
}
#endif
