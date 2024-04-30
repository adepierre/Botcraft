#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class ParticleOptions : public NetworkType
    {
    public:
        virtual ~ParticleOptions();

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
        virtual void WriteImpl(WriteContainer& container) const override;
        virtual Json::Value SerializeImpl() const override;
    };
}
