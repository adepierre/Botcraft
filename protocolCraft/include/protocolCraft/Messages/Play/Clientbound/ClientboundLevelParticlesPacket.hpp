#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include "protocolCraft/Types/Particles/Particle.hpp"

namespace ProtocolCraft
{
    class ClientboundLevelParticlesPacket : public BaseMessage<ClientboundLevelParticlesPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x21;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x22;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Level Particles";

        virtual ~ClientboundLevelParticlesPacket() override
        {

        }


#if PROTOCOL_VERSION < 569
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

        void SetParticle(const std::shared_ptr<Particle>& particle_)
        {
            particle = particle_;
        }


#if PROTOCOL_VERSION < 569
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

        std::shared_ptr<Particle> GetParticle() const
        {
            return particle;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 759
            const ParticleType particle_type = static_cast<ParticleType>(ReadData<int>(iter, length));
#else
            const ParticleType particle_type = static_cast<ParticleType>(static_cast<int>(ReadData<VarInt>(iter, length)));
#endif
            override_limiter = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION < 569
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
            particle = Particle::CreateParticle(particle_type);
            particle->Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 759
            WriteData<int>(static_cast<int>(particle->GetType()), container);
#else
            WriteData<VarInt>(static_cast<int>(particle->GetType()), container);
#endif
            WriteData<bool>(override_limiter, container);
#if PROTOCOL_VERSION < 569
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
            particle->Write(container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["override_limiter"] = override_limiter;
            output["x"] = x;
            output["y"] = y;
            output["z"] = z;
            output["x_dist"] = x_dist;
            output["y_dist"] = y_dist;
            output["z_dist"] = z_dist;
            output["max_speed"] = max_speed;
            output["count"] = count;
            output["particle_type"] = particle->GetName();
            output["particle"] = particle->Serialize();

            return output;
        }

    private:
#if PROTOCOL_VERSION < 569
        float x;
        float y;
        float z;
#else
        double x;
        double y;
        double z;
#endif
        float x_dist;
        float y_dist;
        float z_dist;
        float max_speed;
        int count;
        bool override_limiter;
        std::shared_ptr<Particle> particle;

    };
} //ProtocolCraft
