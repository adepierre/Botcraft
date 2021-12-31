#pragma once

#include "protocolCraft/Types/Particles/Particle.hpp"

namespace ProtocolCraft
{
    class NoDataTypedParticle : public Particle
    {
    public:
        NoDataTypedParticle() = delete;
        NoDataTypedParticle(const ParticleType type_);

        virtual ~NoDataTypedParticle();

        virtual std::string GetName() const override;

        virtual ParticleType GetType() const override;

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override;

        virtual void WriteImpl(WriteContainer& container) const override;

        virtual const nlohmann::json SerializeImpl() const override;

    private:
        ParticleType type;

        static const std::vector<std::string> names;
    };
}
