#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class Particle : public BaseMessage<Particle>
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
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 // 1.16.2, 1.16.3
            return 0x22;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Particle";
        }

        void SetParticleId(const int particle_id_)
        {
            particle_id = particle_id_;
        }

        void SetLongDistance(const bool long_distance_)
        {
            long_distance = long_distance_;
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

        void SetOffsetX(const float offset_x_)
        {
            offset_x = offset_x_;
        }

        void SetOffsetY(const float offset_y_)
        {
            offset_y = offset_y_;
        }

        void SetOffsetZ(const float offset_z_)
        {
            offset_z = offset_z_;
        }

        void SetParticleData(const float particle_data_)
        {
            particle_data = particle_data_;
        }

        void SetParticleCount(const int particle_count_)
        {
            particle_count = particle_count_;
        }

        void SetData(const std::vector<unsigned char>& data_)
        {
            data = data_;
        }


        const int GetParticleId() const
        {
            return particle_id;
        }

        const bool GetLongDistance() const
        {
            return long_distance;
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

        const float GetOffsetX() const
        {
            return offset_x;
        }

        const float GetOffsetY() const
        {
            return offset_y;
        }

        const float GetOffsetZ() const
        {
            return offset_z;
        }

        const float GetParticleData() const
        {
            return particle_data;
        }

        const int GetParticleCount() const
        {
            return particle_count;
        }

        const std::vector<unsigned char>& GetData() const
        {
            return data;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            particle_id = ReadData<int>(iter, length);
            long_distance = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION < 569
            x = ReadData<float>(iter, length);
            y = ReadData<float>(iter, length);
            z = ReadData<float>(iter, length);
#else
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
#endif
            offset_x = ReadData<float>(iter, length);
            offset_y = ReadData<float>(iter, length);
            offset_z = ReadData<float>(iter, length);
            particle_data = ReadData<float>(iter, length);
            particle_count = ReadData<int>(iter, length);
            data = ReadByteArray(iter, length, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<int>(particle_id, container);
            WriteData<bool>(long_distance, container);
#if PROTOCOL_VERSION < 569
            WriteData<float>(x, container);
            WriteData<float>(y, container);
            WriteData<float>(z, container);
#else
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
#endif
            WriteData<float>(offset_x, container);
            WriteData<float>(offset_y, container);
            WriteData<float>(offset_z, container);
            WriteData<float>(particle_data, container);
            WriteData<int>(particle_count, container);
            WriteByteArray(data, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["particle_id"] = picojson::value((double)particle_id);
            object["long_distance"] = picojson::value((double)long_distance);
#if PROTOCOL_VERSION < 569
            object["x"] = picojson::value((double)x);
            object["y"] = picojson::value((double)y);
            object["z"] = picojson::value((double)z);
#else
            object["x"] = picojson::value(x);
            object["y"] = picojson::value(y);
            object["z"] = picojson::value(z);
#endif
            object["offset_x"] = picojson::value((double)offset_x);
            object["offset_y"] = picojson::value((double)offset_y);
            object["offset_z"] = picojson::value((double)offset_z);
            object["particle_data"] = picojson::value((double)particle_data);
            object["particle_count"] = picojson::value((double)particle_count);
            object["data"] = picojson::value("Vector of " + std::to_string(data.size()) + " unsigned chars");

            return value;
        }

    private:
        int particle_id;
        bool long_distance;
#if PROTOCOL_VERSION < 569
        float x;
        float y;
        float z;
#else
        double x;
        double y;
        double z;
#endif
        float offset_x;
        float offset_y;
        float offset_z;
        float particle_data;
        int particle_count;
        std::vector<unsigned char> data;

    };
} //ProtocolCraft