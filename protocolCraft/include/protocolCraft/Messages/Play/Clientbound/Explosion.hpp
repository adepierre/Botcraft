#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include <tuple>

namespace ProtocolCraft
{
    class Explosion : public BaseMessage<Explosion>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x1C;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x1E;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1C;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x1D;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x1C;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4
            return 0x1B;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Explosion";
        }

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

        void SetRadius(const float radius_)
        {
            radius = radius_;
        }

        void SetRecordCount(const int record_count_)
        {
            record_count = record_count_;
        }

        void SetRecords(const std::vector<std::tuple<char, char, char> >& records_)
        {
            records = records_;
        }

        void SetPlayerMotionX(const float player_motion_x_)
        {
            player_motion_x = player_motion_x_;
        }

        void SetPlayerMotionY(const float player_motion_y_)
        {
            player_motion_y = player_motion_y_;
        }

        void SetPlayerMotionZ(const float player_motion_z_)
        {
            player_motion_z = player_motion_z_;
        }


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

        const float GetRadius() const
        {
            return radius;
        }

        const int GetRecordCount() const
        {
            return record_count;
        }

        const std::vector<std::tuple<char, char, char> >& GetRecords() const
        {
            return records;
        }

        const float GetPlayerMotionX() const
        {
            return player_motion_x;
        }

        const float GetPlayerMotionY() const
        {
            return player_motion_y;
        }

        const float GetPlayerMotionZ() const
        {
            return player_motion_z;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            x = ReadData<float>(iter, length);
            y = ReadData<float>(iter, length);
            z = ReadData<float>(iter, length);
            radius = ReadData<float>(iter, length);
            record_count = ReadData<int>(iter, length);
            records = std::vector<std::tuple<char, char, char> >(record_count);
            for (int i = 0; i < record_count; ++i)
            {
                records[i] = std::tuple<char, char, char>(ReadData<char>(iter, length), ReadData<char>(iter, length), ReadData<char>(iter, length));
            }
            player_motion_x = ReadData<float>(iter, length);
            player_motion_y = ReadData<float>(iter, length);
            player_motion_z = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<float>(x, container);
            WriteData<float>(y, container);
            WriteData<float>(z, container);
            WriteData<float>(radius, container);
            WriteData<int>(record_count, container);
            for (int i = 0; i < record_count; ++i)
            {
                WriteData<char>(std::get<0>(records[i]), container);
                WriteData<char>(std::get<1>(records[i]), container);
                WriteData<char>(std::get<2>(records[i]), container);
            }
            WriteData<float>(player_motion_x, container);
            WriteData<float>(player_motion_y, container);
            WriteData<float>(player_motion_z, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["x"] = picojson::value((double)x);
            object["y"] = picojson::value((double)y);
            object["z"] = picojson::value((double)z);
            object["radius"] = picojson::value((double)radius);
            object["record_count"] = picojson::value((double)record_count);
            picojson::value value2(picojson::array_type, false);
            picojson::array& object2 = value2.get<picojson::array>();
            for (int i = 0; i < record_count; ++i)
            {
                object2.push_back(picojson::value((double)(std::get<0>(records[i]))));
                object2.push_back(picojson::value((double)(std::get<1>(records[i]))));
                object2.push_back(picojson::value((double)(std::get<2>(records[i]))));
            }
            object["records"] = value2;
            object["player_motion_x"] = picojson::value((double)player_motion_x);
            object["player_motion_y"] = picojson::value((double)player_motion_y);
            object["player_motion_z"] = picojson::value((double)player_motion_z);

            return value;
        }

    private:
        float x;
        float y;
        float z;
        float radius;
        int record_count;
        std::vector<std::tuple<char, char, char> > records;
        float player_motion_x;
        float player_motion_y;
        float player_motion_z;

    };
} //ProtocolCraft