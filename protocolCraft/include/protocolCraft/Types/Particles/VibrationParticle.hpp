#if PROTOCOL_VERSION > 754
#pragma once

#include "protocolCraft/Types/Particles/Particle.hpp"

#include "protocolCraft/Types/Vibrations/VibrationPath.hpp"

namespace ProtocolCraft
{
    class VibrationParticle : public Particle
    {
    public:
        VibrationParticle();
        
        virtual ~VibrationParticle();
        
        virtual std::string GetName() const override;
        
        virtual ParticleType GetType() const override;

        const VibrationPath& GetVibrationPath() const;

        void SetVibrationPath(const VibrationPath& vibration_path_);
        
    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override;
        
        virtual void WriteImpl(WriteContainer &container) const override;
        
        virtual Json::Value SerializeImpl() const override;

    private:
        VibrationPath vibration_path;
        
    };
}
#endif
