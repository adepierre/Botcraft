#if PROTOCOL_VERSION > 392
#pragma once

#include "protocolCraft/Types/Particles/Particle.hpp"

namespace ProtocolCraft
{
    class DustParticle : public Particle
    {
    public:
        DustParticle();
        
        virtual ~DustParticle();
        
        virtual std::string GetName() const override;
        
        virtual ParticleType GetType() const override;

        float GetRed() const;
        float GetGreen() const;
        float GetBlue() const;
        float GetScale() const;

        void SetRed(const float red_);
        void SetGreen(const float green_);
        void SetBlue(const float blue_);
        void SetScale(const float scale_);
        
    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override;
        
        virtual void WriteImpl(WriteContainer &container) const override;
        
        virtual Json::Value SerializeImpl() const override;

    private:
        float red;
        float green;
        float blue;
        float scale;
        
    };
}
#endif
