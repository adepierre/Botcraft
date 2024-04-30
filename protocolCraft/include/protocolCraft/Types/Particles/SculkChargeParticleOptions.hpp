#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class SculkChargeParticleOptions : public ParticleOptions
    {
    public:
        SculkChargeParticleOptions();
        
        virtual ~SculkChargeParticleOptions();

        float GetRoll() const;

        void SetRoll(const float roll_);
        
    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
        virtual void WriteImpl(WriteContainer& container) const override;
        virtual Json::Value SerializeImpl() const override;
        
    private:
        float roll = 0.0f;
    };
}
#endif
