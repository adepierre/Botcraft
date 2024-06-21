#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include "protocolCraft/Types/Particles/Particle.hpp"

namespace ProtocolCraft
{
    class ClientboundLevelParticlesPacket : public BaseMessage<ClientboundLevelParticlesPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Level Particles";

#if PROTOCOL_VERSION < 573 /* < 1.15 */
        DECLARE_FIELDS(
            (bool,            float, float, float, float, float, float, float,    int,   Particle),
            (OverrideLimiter, X,     Y,     Z,     XDist, YDist, ZDist, MaxSpeed, Count, Particle)
        );
#else
        DECLARE_FIELDS(
            (bool,            double, double, double, float, float, float, float,    int,   Particle),
            (OverrideLimiter, X,      Y,      Z,      XDist, YDist, ZDist, MaxSpeed, Count, Particle)
        );
#endif
        DECLARE_SERIALIZE;

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

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
            const ParticleType particle_type = ReadData<ParticleType, int>(iter, length);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
            const ParticleType particle_type = ReadData<ParticleType, VarInt>(iter, length);
#endif
            SetOverrideLimiter(ReadData<bool>(iter, length));
#if PROTOCOL_VERSION < 569 /* < 1.15 */
            SetX(ReadData<float>(iter, length));
            SetY(ReadData<float>(iter, length));
            SetZ(ReadData<float>(iter, length));
#else
            SetX(ReadData<double>(iter, length));
            SetY(ReadData<double>(iter, length));
            SetZ(ReadData<double>(iter, length));
#endif
            SetXDist(ReadData<float>(iter, length));
            SetYDist(ReadData<float>(iter, length));
            SetZDist(ReadData<float>(iter, length));
            SetMaxSpeed(ReadData<float>(iter, length));
            SetCount(ReadData<int>(iter, length));
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            Particle particle;
            particle.SetParticleType(static_cast<ParticleType>(particle_type));
            particle.ReadOptions(iter, length);
            SetParticle(particle);
#else
            SetParticle(ReadData<Particle>(iter, length));
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
            WriteData<ParticleType, int>(GetParticle().GetParticleType(), container);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
            WriteData<ParticleType, VarInt>(GetParticle().GetParticleType(), container);
#endif
            WriteData<bool>(GetOverrideLimiter(), container);
#if PROTOCOL_VERSION < 569 /* < 1.15 */
            WriteData<float>(GetX(), container);
            WriteData<float>(GetY(), container);
            WriteData<float>(GetZ(), container);
#else
            WriteData<double>(GetX(), container);
            WriteData<double>(GetY(), container);
            WriteData<double>(GetZ(), container);
#endif
            WriteData<float>(GetXDist(), container);
            WriteData<float>(GetYDist(), container);
            WriteData<float>(GetZDist(), container);
            WriteData<float>(GetMaxSpeed(), container);
            WriteData<int>(GetCount(), container);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            GetParticle().WriteOptions(container);
#else
            WriteData<Particle>(GetParticle(), container);
#endif
        }
    };
} //ProtocolCraft
