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
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x1A;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x20;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Explode";

        virtual ~ClientboundExplodePacket() override
        {

        }

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        void SetX(const float x_)
        {
            x = x_;
        }

        void SetY(const float y_)
        {
            y = y_;
        }

        void SetZ(const float z_)
        {
            z = z_;
        }
#else
        void SetX(const double x_)
        {
            x = x_;
        }

        void SetY(const double y_)
        {
            y = y_;
        }

        void SetZ(const double z_)
        {
            z = z_;
        }
#endif

        void SetPower(const float power_)
        {
            power = power_;
        }

        void SetToBlow(const std::vector<NetworkPosition>& to_blow_)
        {
            to_blow = to_blow_;
        }

        void SetKnockbackX(const float knockback_x_)
        {
            knockback_x = knockback_x_;
        }

        void SetKnockbackY(const float knockback_y_)
        {
            knockback_y = knockback_y_;
        }

        void SetKnockbackZ(const float knockback_z_)
        {
            knockback_z = knockback_z_;
        }

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        void SetSmallExplosionParticles(const Particle& small_explosion_particles_)
        {
            small_explosion_particles = small_explosion_particles_;
        }

        void SetLargeExplosionParticles(const Particle& large_explosion_particles_)
        {
            large_explosion_particles = large_explosion_particles_;
        }

        void SetBlockInteraction(const int block_interaction_)
        {
            block_interaction = block_interaction_;
        }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        void SetExplosionSound(const SoundEvent& explosion_sound_)
        {
            explosion_sound = explosion_sound_;
        }
#else
        void SetExplosionSound(const Holder<SoundEvent>& explosion_sound_)
        {
            explosion_sound = explosion_sound_;
        }
#endif
#endif


#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        float GetX() const
        {
            return x;
        }

        float GetY() const
        {
            return y;
        }

        float GetZ() const
        {
            return z;
        }
#else

        double GetX() const
        {
            return x;
        }

        double GetY() const
        {
            return y;
        }

        double GetZ() const
        {
            return z;
        }
#endif

        float GetPower() const
        {
            return power;
        }

        const std::vector<NetworkPosition>& GetToBlow() const
        {
            return to_blow;
        }

        float GetKnockbackX() const
        {
            return knockback_x;
        }

        float GetKnockbackY() const
        {
            return knockback_y;
        }

        float GetKnockbackZ() const
        {
            return knockback_z;
        }

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        const Particle& GetSmallExplosionParticles() const
        {
            return small_explosion_particles;
        }

        const Particle& GetLargeExplosionParticles() const
        {
            return large_explosion_particles;
        }

        int GetBlockInteraction() const
        {
            return block_interaction;
        }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        const SoundEvent& GetExplosionSound() const
        {
            return explosion_sound;
        }
#else
        const Holder<SoundEvent>& GetExplosionSound() const
        {
            return explosion_sound;
        }
#endif
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            x = ReadData<float>(iter, length);
            y = ReadData<float>(iter, length);
            z = ReadData<float>(iter, length);
#else
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
#endif
            power = ReadData<float>(iter, length);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            // Special case, read size as int instead of VarInt, and custom read function
            to_blow = ReadVector<NetworkPosition, int>(iter, length,
#else
            to_blow = ReadVector<NetworkPosition>(iter, length,
#endif
                [](ReadIterator& i, size_t& l)
                {
                    NetworkPosition output;

                    output.SetX(static_cast<int>(ReadData<char>(i, l)));
                    output.SetY(static_cast<int>(ReadData<char>(i, l)));
                    output.SetZ(static_cast<int>(ReadData<char>(i, l)));

                    return output;
                }
            );
            knockback_x = ReadData<float>(iter, length);
            knockback_y = ReadData<float>(iter, length);
            knockback_z = ReadData<float>(iter, length);
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            block_interaction = ReadData<VarInt>(iter, length);
            small_explosion_particles = ReadData<Particle>(iter, length);
            large_explosion_particles = ReadData<Particle>(iter, length);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            explosion_sound = ReadData<SoundEvent>(iter, length);
#else
            explosion_sound = ReadData<Holder<SoundEvent>>(iter, length);
#endif
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            WriteData<float>(x, container);
            WriteData<float>(y, container);
            WriteData<float>(z, container);
#else
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
#endif
            WriteData<float>(power, container);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            // Special case, write size as int instead of VarInt, with custom write function
            WriteVector<NetworkPosition, int>(to_blow, container,
#else
            WriteVector<NetworkPosition>(to_blow, container,
#endif
                [](const NetworkPosition& n, WriteContainer& c)
                {
                    WriteData<char>(static_cast<char>(n.GetX()), c);
                    WriteData<char>(static_cast<char>(n.GetY()), c);
                    WriteData<char>(static_cast<char>(n.GetZ()), c);
                }
            );
            WriteData<float>(knockback_x, container);
            WriteData<float>(knockback_y, container);
            WriteData<float>(knockback_z, container);
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            WriteData<VarInt>(block_interaction, container);
            WriteData<Particle>(small_explosion_particles, container);
            WriteData<Particle>(large_explosion_particles, container);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            WriteData<SoundEvent>(explosion_sound, container);
#else
            WriteData<Holder<SoundEvent>>(explosion_sound, container);
#endif
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["x"] = x;
            output["y"] = y;
            output["z"] = z;
            output["power"] = power;
            output["to_blow"] = to_blow;
            output["knockback_x"] = knockback_x;
            output["knockback_y"] = knockback_y;
            output["knockback_z"] = knockback_z;
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            output["block_interaction"] = block_interaction;
            output["small_explosion_particles"] = small_explosion_particles;
            output["large_explosion_particles"] = large_explosion_particles;
            output["explosion_sound"] = explosion_sound;
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
#else
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
#endif
        float power = 0.0f;
        std::vector<NetworkPosition> to_blow;
        float knockback_x = 0.0f;
        float knockback_y = 0.0f;
        float knockback_z = 0.0f;
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        Particle small_explosion_particles;
        Particle large_explosion_particles;
        int block_interaction;
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SoundEvent explosion_sound;
#else
        Holder<SoundEvent> explosion_sound;
#endif
#endif

    };
} //ProtocolCraft
