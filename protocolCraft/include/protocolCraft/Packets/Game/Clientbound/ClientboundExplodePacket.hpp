#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Types/Particles/Particle.hpp"
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Holder.hpp"
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "protocolCraft/Types/Particles/ExplosionParticleInfo.hpp"
#endif

#include <array>
#include <optional>
#include <vector>

namespace ProtocolCraft
{
    class ClientboundExplodePacket : public BasePacket<ClientboundExplodePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Explode";

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        SERIALIZED_FIELD(X, float);
        SERIALIZED_FIELD(Y, float);
        SERIALIZED_FIELD(Z, float);
#elif PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
#else
        SERIALIZED_FIELD(Center, std::array<double, 3>);
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        SERIALIZED_FIELD(Radius, float);
        SERIALIZED_FIELD(BlockCount, int);
#endif
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(Power, float);
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        SERIALIZED_FIELD(ToBlow, Internal::Vector<std::array<char, 3>, int>);
#elif PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(ToBlow, std::vector<std::array<char, 3>>);
#endif
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(KnockbackX, float);
        SERIALIZED_FIELD(KnockbackY, float);
        SERIALIZED_FIELD(KnockbackZ, float);
#else
        SERIALIZED_FIELD(PlayerKnockback, std::optional<std::array<double, 3>>);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */ && PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(BlockInteraction, VarInt);
        SERIALIZED_FIELD(SmallExplosionParticles, Particle);
        SERIALIZED_FIELD(LargeExplosionParticles, Particle);
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        SERIALIZED_FIELD(ExplosionParticle, Particle);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */ && PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD(ExplosionSound, SoundEvent);
#elif PROTOCOL_VERSION > 764 /* > 1.20.2 */
        SERIALIZED_FIELD(ExplosionSound, Holder<SoundEvent>);
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        SERIALIZED_FIELD(BlockParticles, std::vector<std::pair<ExplosionParticleInfo, VarInt>>);
#endif
#if PROTOCOL_VERSION > 776 /* > 26.2 */
        SERIALIZED_FIELD(PlaySound, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
