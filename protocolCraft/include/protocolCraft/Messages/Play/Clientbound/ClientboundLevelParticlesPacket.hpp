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
#elif PROTOCOL_VERSION == 766 /* 1.20.5 */
        static constexpr int packet_id = 0x29;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Level Particles";

        virtual ~ClientboundLevelParticlesPacket() override
        {

        }


#if PROTOCOL_VERSION < 569 /* < 1.15 */
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

        void SetXDist(const float x_dist_)
        {
            x_dist = x_dist_;
        }

        void SetYDist(const float y_dist_)
        {
            y_dist = y_dist_;
        }

        void SetZDist(const float z_dist_)
        {
            z_dist = z_dist_;
        }

        void SetMaxSpeed(const float max_speed_)
        {
            max_speed = max_speed_;
        }

        void SetCount(const int count_)
        {
            count = count_;
        }

        void SetOverrideLimiter(const bool override_limiter_)
        {
            override_limiter = override_limiter_;
        }

        void SetParticle(const Particle& particle_)
        {
            particle = particle_;
        }


#if PROTOCOL_VERSION < 569 /* < 1.15 */
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

        float GetXDist() const
        {
            return x_dist;
        }

        float GetYDist() const
        {
            return y_dist;
        }

        float GetZDist() const
        {
            return z_dist;
        }

        float GetMaxSpeed() const
        {
            return max_speed;
        }

        int GetCount() const
        {
            return count;
        }

        bool GetOverrideLimiter() const
        {
            return override_limiter;
        }

        const Particle& GetParticle() const
        {
            return particle;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
            const ParticleType particle_type = static_cast<ParticleType>(ReadData<int>(iter, length));
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
            const ParticleType particle_type = static_cast<ParticleType>(static_cast<int>(ReadData<VarInt>(iter, length)));
#endif
            override_limiter = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION < 569 /* < 1.15 */
            x = ReadData<float>(iter, length);
            y = ReadData<float>(iter, length);
            z = ReadData<float>(iter, length);
#else
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
#endif
            x_dist = ReadData<float>(iter, length);
            y_dist = ReadData<float>(iter, length);
            z_dist = ReadData<float>(iter, length);
            max_speed = ReadData<float>(iter, length);
            count = ReadData<int>(iter, length);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            particle.SetParticleType(static_cast<ParticleType>(particle_type));
            particle.ReadOptions(iter, length);
#else
            particle = ReadData<Particle>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
            WriteData<int>(static_cast<int>(particle->GetType()), container);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
            WriteData<VarInt>(static_cast<int>(particle->GetType()), container);
#endif
            WriteData<bool>(override_limiter, container);
#if PROTOCOL_VERSION < 569 /* < 1.15 */
            WriteData<float>(x, container);
            WriteData<float>(y, container);
            WriteData<float>(z, container);
#else
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
#endif
            WriteData<float>(x_dist, container);
            WriteData<float>(y_dist, container);
            WriteData<float>(z_dist, container);
            WriteData<float>(max_speed, container);
            WriteData<int>(count, container);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            particle.WriteOptions(container);
#else
            WriteData<Particle>(particle, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["override_limiter"] = override_limiter;
            output["x"] = x;
            output["y"] = y;
            output["z"] = z;
            output["x_dist"] = x_dist;
            output["y_dist"] = y_dist;
            output["z_dist"] = z_dist;
            output["max_speed"] = max_speed;
            output["count"] = count;
            output["particle"] = particle;

            return output;
        }

    private:
#if PROTOCOL_VERSION < 569 /* < 1.15 */
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
#else
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
#endif
        float x_dist = 0.0f;
        float y_dist = 0.0f;
        float z_dist = 0.0f;
        float max_speed = 0.0f;
        int count = 0;
        bool override_limiter = false;
        Particle particle;

    };
} //ProtocolCraft
