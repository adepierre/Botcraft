#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class UpdateSign : public BaseMessage<UpdateSign>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x1C;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x26;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x29;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x29;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
            return 0x2A;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update Sign";
        }

        void SetLocation(const NetworkPosition& location_)
        {
            location = location_;
        }

        void SetLine1(const std::string& line_1_)
        {
            line_1 = line_1_;
        }

        void SetLine2(const std::string& line_2_)
        {
            line_2 = line_2_;
        }

        void SetLine3(const std::string& line_3_)
        {
            line_3 = line_3_;
        }

        void SetLine4(const std::string& line_4_)
        {
            line_4 = line_4_;
        }


        const NetworkPosition& GetLocation() const
        {
            return location;
        }

        const std::string& GetLine1() const
        {
            return line_1;
        }

        const std::string& GetLine2() const
        {
            return line_2;
        }

        const std::string& GetLine3() const
        {
            return line_3;
        }

        const std::string& GetLine4() const
        {
            return line_4;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            location.Read(iter, length);
            line_1 = ReadString(iter, length);
            line_2 = ReadString(iter, length);
            line_3 = ReadString(iter, length);
            line_4 = ReadString(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            location.Write(container);
            WriteString(line_1, container);
            WriteString(line_2, container);
            WriteString(line_3, container);
            WriteString(line_4, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["location"] = location.Serialize();
            object["line_1"] = picojson::value(line_1);
            object["line_2"] = picojson::value(line_2);
            object["line_3"] = picojson::value(line_3);
            object["line_4"] = picojson::value(line_4);

            return value;
        }

    private:
        NetworkPosition location;
        std::string line_1;
        std::string line_2;
        std::string line_3;
        std::string line_4;

    };
} //ProtocolCraft