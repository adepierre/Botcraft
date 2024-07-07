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
        DECLARE_FIELDS(
            (float, float, float, float, Internal::CustomType<std::vector<NetworkPosition>, &THIS::ReadToBlow, &THIS::WriteToBlow>, float,      float,      float),
            (X,     Y,     Z,     Power, ToBlow,                                                                                    KnockbackX, KnockbackY, KnockbackZ)
        );
#elif PROTOCOL_VERSION < 765 /* < 1.20.3 */
        DECLARE_FIELDS(
            (double, double, double, float, Internal::CustomType<std::vector<NetworkPosition>, &THIS::ReadToBlow, &THIS::WriteToBlow>, float,      float,      float),
            (X,      Y,      Z,      Power, ToBlow,                                                                                    KnockbackX, KnockbackY, KnockbackZ)
        );
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS(
            (double, double, double, float, Internal::CustomType<std::vector<NetworkPosition>, &THIS::ReadToBlow, &THIS::WriteToBlow>, float,      float,      float,      VarInt,           Particle,                Particle,                SoundEvent),
            (X,      Y,      Z,      Power, ToBlow,                                                                                    KnockbackX, KnockbackY, KnockbackZ, BlockInteraction, SmallExplosionParticles, LargeExplosionParticles, ExplosionSound)
        );
#else
        DECLARE_FIELDS(
            (double, double, double, float, Internal::CustomType<std::vector<NetworkPosition>, &THIS::ReadToBlow, &THIS::WriteToBlow>, float,      float,      float,      VarInt,           Particle,                Particle,                Holder<SoundEvent>),
            (X,      Y,      Z,      Power, ToBlow,                                                                                    KnockbackX, KnockbackY, KnockbackZ, BlockInteraction, SmallExplosionParticles, LargeExplosionParticles, ExplosionSound)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(X);
        GETTER_SETTER(Y);
        GETTER_SETTER(Z);
        GETTER_SETTER(Power);
        GETTER_SETTER(ToBlow);
        GETTER_SETTER(KnockbackX);
        GETTER_SETTER(KnockbackY);
        GETTER_SETTER(KnockbackZ);
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        GETTER_SETTER(BlockInteraction);
        GETTER_SETTER(SmallExplosionParticles);
        GETTER_SETTER(LargeExplosionParticles);
        GETTER_SETTER(ExplosionSound);
#endif
    };
} //ProtocolCraft
