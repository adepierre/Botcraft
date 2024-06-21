#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"
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

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS(
            (float, float, float, float, std::vector<NetworkPosition>, float,      float,      float),
            (X,     Y,     Z,     Power, ToBlow,                       KnockbackX, KnockbackY, KnockbackZ)
        );
#elif PROTOCOL_VERSION < 765 /* < 1.20.3 */
        DECLARE_FIELDS(
            (double, double, double, float, std::vector<NetworkPosition>, float,      float,      float),
            (X,      Y,      Z,      Power, ToBlow,                       KnockbackX, KnockbackY, KnockbackZ)
        );
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS(
            (double, double, double, float, std::vector<NetworkPosition>, float,      float,      float,      VarInt,           Particle,                Particle,                SoundEvent),
            (X,      Y,      Z,      Power, ToBlow,                       KnockbackX, KnockbackY, KnockbackZ, BlockInteraction, SmallExplosionParticles, LargeExplosionParticles, ExplosionSound)
        );
#else
        DECLARE_FIELDS(
            (double, double, double, float, std::vector<NetworkPosition>, float,      float,      float,      VarInt,           Particle,                Particle,                Holder<SoundEvent>),
            (X,      Y,      Z,      Power, ToBlow,                       KnockbackX, KnockbackY, KnockbackZ, BlockInteraction, SmallExplosionParticles, LargeExplosionParticles, ExplosionSound)
        );
#endif
        DECLARE_SERIALIZE;

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

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            SetX(ReadData<float>(iter, length));
            SetY(ReadData<float>(iter, length));
            SetZ(ReadData<float>(iter, length));
#else
            SetX(ReadData<double>(iter, length));
            SetY(ReadData<double>(iter, length));
            SetZ(ReadData<double>(iter, length));
#endif
            SetPower(ReadData<float>(iter, length));
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            // Special case, read size as int instead of VarInt, and custom read function
            SetToBlow(ReadVector<NetworkPosition, int>(iter, length,
#else
            SetToBlow(ReadVector<NetworkPosition>(iter, length,
#endif
                [](ReadIterator& i, size_t& l)
                {
                    NetworkPosition output;

                    output.SetX(ReadData<int, char>(i, l));
                    output.SetY(ReadData<int, char>(i, l));
                    output.SetZ(ReadData<int, char>(i, l));

                    return output;
                }
            ));
            SetKnockbackX(ReadData<float>(iter, length));
            SetKnockbackY(ReadData<float>(iter, length));
            SetKnockbackZ(ReadData<float>(iter, length));
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            SetBlockInteraction(ReadData<VarInt>(iter, length));
            SetSmallExplosionParticles(ReadData<Particle>(iter, length));
            SetLargeExplosionParticles(ReadData<Particle>(iter, length));
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            SetExplosionSound(ReadData<SoundEvent>(iter, length));
#else
            SetExplosionSound(ReadData<Holder<SoundEvent>>(iter, length));
#endif
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            WriteData<float>(GetX(), container);
            WriteData<float>(GetY(), container);
            WriteData<float>(GetZ(), container);
#else
            WriteData<double>(GetX(), container);
            WriteData<double>(GetY(), container);
            WriteData<double>(GetZ(), container);
#endif
            WriteData<float>(GetPower(), container);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            // Special case, write size as int instead of VarInt, with custom write function
            WriteVector<NetworkPosition, int>(GetToBlow(), container,
#else
            WriteVector<NetworkPosition>(GetToBlow(), container,
#endif
                [](const NetworkPosition& n, WriteContainer& c)
                {
                    WriteData<int, char>(n.GetX(), c);
                    WriteData<int, char>(n.GetY(), c);
                    WriteData<int, char>(n.GetZ(), c);
                }
            );
            WriteData<float>(GetKnockbackX(), container);
            WriteData<float>(GetKnockbackY(), container);
            WriteData<float>(GetKnockbackZ(), container);
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            WriteData<VarInt>(GetBlockInteraction(), container);
            WriteData<Particle>(GetSmallExplosionParticles(), container);
            WriteData<Particle>(GetLargeExplosionParticles(), container);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            WriteData<SoundEvent>(GetExplosionSound(), container);
#else
            WriteData<Holder<SoundEvent>>(GetExplosionSound(), container);
#endif
#endif
        }
    };
} //ProtocolCraft
