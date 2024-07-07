#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include "protocolCraft/Types/Particles/Particle.hpp"

namespace ProtocolCraft
{
    class ClientboundLevelParticlesPacket : public BaseMessage<ClientboundLevelParticlesPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Level Particles";

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    private:
        Particle ReadParticle(ReadIterator& iter, size_t& length) const
        {
            Particle particle;
            particle.SetParticleType(GetParticleType());
            particle.ReadOptions(iter, length);
            return particle;
        }

        void WriteParticle(const Particle& particle, WriteContainer& container) const
        {
            particle.WriteOptions(container);
        }
#endif

#if PROTOCOL_VERSION < 573 /* < 1.15 */
        DECLARE_FIELDS(
            (Internal::DiffType<ParticleType, int>, bool,            float, float, float, float, float, float, float,    int,   Internal::CustomType<Particle, &THIS::ReadParticle, &THIS::WriteParticle>),
            (ParticleType,                          OverrideLimiter, X,     Y,     Z,     XDist, YDist, ZDist, MaxSpeed, Count, Particle)
        );
#elif PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS(
            (Internal::DiffType<ParticleType, int>, bool,            double, double, double, float, float, float, float,    int,   Internal::CustomType<Particle, &THIS::ReadParticle, &THIS::WriteParticle>),
            (ParticleType,                          OverrideLimiter, X,      Y,      Z,      XDist, YDist, ZDist, MaxSpeed, Count, Particle)
        );
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS(
            (Internal::DiffType<ParticleType, VarInt>, bool,            double, double, double, float, float, float, float,    int,   Internal::CustomType<Particle, &THIS::ReadParticle, &THIS::WriteParticle>),
            (ParticleType,                             OverrideLimiter, X,      Y,      Z,      XDist, YDist, ZDist, MaxSpeed, Count, Particle)
        );
#else
        DECLARE_FIELDS(
            (bool,            double, double, double, float, float, float, float,    int,   Particle),
            (OverrideLimiter, X,      Y,      Z,      XDist, YDist, ZDist, MaxSpeed, Count, Particle)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        GETTER_SETTER(ParticleType);
#endif
        GETTER_SETTER(OverrideLimiter);
        GETTER_SETTER(X);
        GETTER_SETTER(Y);
        GETTER_SETTER(Z);
        GETTER_SETTER(XDist);
        GETTER_SETTER(YDist);
        GETTER_SETTER(ZDist);
        GETTER_SETTER(MaxSpeed);
        GETTER_SETTER(Count);
        GETTER_SETTER(Particle);
    };
} //ProtocolCraft
