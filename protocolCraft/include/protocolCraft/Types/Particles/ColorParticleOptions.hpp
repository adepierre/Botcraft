#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class ColorParticleOptions : public ParticleOptions
    {
    public:
        ColorParticleOptions();
        virtual ~ColorParticleOptions();

        int GetColor() const;

        void SetColor(const int color_);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
        virtual void WriteImpl(WriteContainer& container) const override;
        virtual Json::Value SerializeImpl() const override;

    private:
        int color = 0;
    };
}
#endif
