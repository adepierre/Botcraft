#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include "protocolCraft/Types/Particles/Particle.hpp"

namespace ProtocolCraft
{
    class ClientboundLevelParticlesPacket : public BaseMessage<ClientboundLevelParticlesPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x21;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x26;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x29;
#else
#error "Protocol version not implemented"
#endif

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
