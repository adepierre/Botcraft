#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Utilities/CustomType.hpp"

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
            ProtocolCraft::Particle particle;
            particle.SetParticleType(GetParticleType());
            particle.ReadOptions(iter, length);
            return particle;
        }

        void WriteParticle(const Particle& particle, WriteContainer& container) const
        {
            particle.WriteOptions(container);
        }
#endif

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        SERIALIZED_FIELD(ParticleType, Internal::DiffType<ProtocolCraft::ParticleType, int>);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD(ParticleType, Internal::DiffType<ProtocolCraft::ParticleType, VarInt>);
#endif
        SERIALIZED_FIELD(OverrideLimiter, bool);
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
        SERIALIZED_FIELD(AlwaysShow, bool);
#endif
        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
        SERIALIZED_FIELD(XDist, float);
        SERIALIZED_FIELD(YDist, float);
        SERIALIZED_FIELD(ZDist, float);
        SERIALIZED_FIELD(MaxSpeed, float);
        SERIALIZED_FIELD(Count, int);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD(ParticleData, Internal::CustomType<ProtocolCraft::Particle, &THIS::ReadParticle, &THIS::WriteParticle>);
#else
        SERIALIZED_FIELD(Particle, ProtocolCraft::Particle);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
