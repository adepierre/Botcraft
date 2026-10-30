#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Particles/Particle.hpp"
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
#include "protocolCraft/Types/Particles/ParticleOption.hpp"
#include "protocolCraft/Utilities/DynamicType.hpp"
#endif


namespace ProtocolCraft
{
    class ClientboundLevelParticlesPacket : public BasePacket<ClientboundLevelParticlesPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Level Particles";

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(ParticleType, Internal::DiffType<ProtocolCraft::ParticleType, int>);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(ParticleType, Internal::DiffType<ProtocolCraft::ParticleType, VarInt>);
#elif PROTOCOL_VERSION > 776 /* > 26.2 */
        SERIALIZED_FIELD(Particle, ProtocolCraft::Particle);
#endif
        SERIALIZED_FIELD(OverrideLimiter, bool);
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
        SERIALIZED_FIELD(AlwaysShow, bool);
#endif
#if PROTOCOL_VERSION < 573 /* < 1.15 */
        SERIALIZED_FIELD(X, float);
        SERIALIZED_FIELD(Y, float);
        SERIALIZED_FIELD(Z, float);
#else
        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
#endif
        SERIALIZED_FIELD(XDist, float);
        SERIALIZED_FIELD(YDist, float);
        SERIALIZED_FIELD(ZDist, float);
#if PROTOCOL_VERSION < 777 /* < 26.3 */
        SERIALIZED_FIELD(MaxSpeed, float);
        SERIALIZED_FIELD(Count, int);
#else
        SERIALIZED_FIELD(XMaxSpeed, float);
        SERIALIZED_FIELD(YMaxSpeed, float);
        SERIALIZED_FIELD(ZMaxSpeed, float);
        SERIALIZED_FIELD(Count, VarInt);
        SERIALIZED_FIELD(RandomizationType, VarInt);
#endif
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_DYNAMIC_DATA_FIELD(ParticleData, THIS::ParticleType, ParticleOption, Particle::CreateParticleOption);
#elif PROTOCOL_VERSION < 777 /* < 26.3 */
        SERIALIZED_FIELD(Particle, ProtocolCraft::Particle);
#endif

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        GETTER(ParticleType);
        DYNAMIC_TYPE_SETTER(ParticleType, ParticleData, Particle::CreateParticleOption);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
