#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class ShriekParticleOptions : public ParticleOptions
    {
    public:
        ShriekParticleOptions();
        
        virtual ~ShriekParticleOptions();

        int GetDelay() const;

        void SetDelay(const int delay_);
        
    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
        virtual void WriteImpl(WriteContainer& container) const override;
        virtual Json::Value SerializeImpl() const override;
        
    private:
        int delay = 0;
    };
}
#endif
