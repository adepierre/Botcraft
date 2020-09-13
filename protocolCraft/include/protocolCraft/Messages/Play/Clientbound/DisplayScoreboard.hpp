#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class DisplayScoreboard : public BaseMessage<DisplayScoreboard>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x39;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x3E;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x42;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x43;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x43;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 // 1.16.2, 1.16.3
            return 0x43;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Display Scoreboard";
        }

        void SetPosition(const NetworkPosition& Position_)
        {
            position = Position_;
        }

        void SetScoreName(const std::string& score_name_)
        {
            score_name = score_name_;
        }


        const NetworkPosition& GetPosition() const
        {
            return position;
        }

        const std::string& GetScoreName() const
        {
            return score_name;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            position.Read(iter, length);
            score_name = ReadString(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            position.Write(container);
            WriteString(score_name, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["Position"] = position.Serialize();
            object["score_name"] = picojson::value(score_name);

            return value;
        }

    private:
        NetworkPosition position;
        std::string score_name;

    };
} //ProtocolCraft