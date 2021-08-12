#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundLevelParticlesPacket : public BaseMessage<ClientboundLevelParticlesPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x22;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x24;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x23;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x24;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x23;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x22;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x24;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Level Particles";
        }

        virtual ~ClientboundLevelParticlesPacket() override
        {

        }

        void SetParticleType(const int particle_type_)
        {
            particle_type = particle_type_;
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

        void SetParticleData(const float particle_data_)
        {
            particle_data = particle_data_;
        }

        void SetCount(const int count_)
        {
            count = count_;
        }

        void SetOverrideLimiter(const bool override_limiter_)
        {
            override_limiter = override_limiter_;
        }

        void SetData(const std::vector<unsigned char>& data_)
        {
            data = data_;
        }


        const int GetParticleType() const
        {
            return particle_type;
        }

#if PROTOCOL_VERSION < 569
        const float GetX() const
        {
            return x;
        }

        const float GetY() const
        {
            return y;
        }

        const float GetZ() const
        {
            return z;
        }
#else
        const double GetX() const
        {
            return x;
        }

        const double GetY() const
        {
            return y;
        }

        const double GetZ() const
        {
            return z;
        }
#endif

        const float GetXDist() const
        {
            return x_dist;
        }

        const float GetYDist() const
        {
            return y_dist;
        }

        const float GetZDist() const
        {
            return z_dist;
        }

        const float GetParticleData() const
        {
            return particle_data;
        }

        const int GetCount() const
        {
            return count;
        }

        const bool GetOverrideLimiter() const
        {
            return override_limiter;
        }

        const std::vector<unsigned char>& GetData() const
        {
            return data;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            particle_type = ReadData<int>(iter, length);
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
            particle_data = ReadData<float>(iter, length);
            count = ReadData<int>(iter, length);
            data = ReadByteArray(iter, length, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<int>(particle_type, container);
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
            WriteData<float>(particle_data, container);
            WriteData<int>(count, container);
            WriteByteArray(data, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["particle_type"] = particle_type;
            output["override_limiter"] = override_limiter;
#if PROTOCOL_VERSION < 569
            output["x"] = x;
            output["y"] = y;
            output["z"] = z;
#else
            output["x"] = x;
            output["y"] = y;
            output["z"] = z;
#endif
            output["x_dist"] = x_dist;
            output["y_dist"] = y_dist;
            output["z_dist"] = z_dist;
            output["particle_data"] = particle_data;
            output["count"] = count;
            output["data"] = "Vector of " + std::to_string(data.size()) + " unsigned chars";

            return output;
        }

    private:
        int particle_type;
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
        float particle_data;
        int count;
        bool override_limiter;
        std::vector<unsigned char> data;

    };
} //ProtocolCraft