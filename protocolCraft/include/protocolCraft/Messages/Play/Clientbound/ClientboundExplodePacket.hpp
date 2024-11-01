#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"
#include "protocolCraft/Utilities/CustomType.hpp"
#include "protocolCraft/Utilities/CustomType.hpp"
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Types/Particles/Particle.hpp"
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Holder.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundExplodePacket : public BaseMessage<ClientboundExplodePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Explode";

    private:
        std::vector<NetworkPosition> ReadToBlow(ReadIterator& iter, size_t& length) const
        {
            std::vector<NetworkPosition> to_blow(
#if PROTOCOL_VERSION < 755 /* < 1.17 */
                ReadData<int>(iter, length)
#else
                ReadData<VarInt>(iter, length)
#endif
            );

            for (size_t i = 0; i < to_blow.size(); ++i)
            {
                to_blow[i].SetX(ReadData<int, char>(iter, length));
                to_blow[i].SetY(ReadData<int, char>(iter, length));
                to_blow[i].SetZ(ReadData<int, char>(iter, length));
            }

            return to_blow;
        }

        void WriteToBlow(const std::vector<NetworkPosition>& to_blow, WriteContainer& container) const
        {
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            WriteData<int>(static_cast<int>(to_blow.size()), container);
#else
            WriteData<VarInt>(static_cast<int>(to_blow.size()), container);
#endif

            for (size_t i = 0; i < to_blow.size(); ++i)
            {
                WriteData<int, char>(to_blow[i].GetX(), container);
                WriteData<int, char>(to_blow[i].GetY(), container);
                WriteData<int, char>(to_blow[i].GetZ(), container);
            }
        }

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
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(Power, float);
        SERIALIZED_FIELD(ToBlow, Internal::CustomType<std::vector<NetworkPosition>, &THIS::ReadToBlow, &THIS::WriteToBlow>);
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

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
