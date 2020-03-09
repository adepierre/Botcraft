#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat.hpp"

namespace ProtocolCraft
{
    class ChatMessageClientbound : public BaseMessage<ChatMessageClientbound>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x0F;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x0E;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x0E;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x0F;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Chat Message (clientbound)";
        }

        void SetJsonData(const Chat& json_data_)
        {
            json_data = json_data_;
        }

        void SetPosition(const char position_)
        {
            position = position_;
        }

        const Chat& GetJsonData() const
        {
            return json_data;
        }

        const char GetPosition() const
        {
            return position;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            json_data.Read(iter, length);
            position = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            json_data.Write(container);
            WriteData<char>(position, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["json_data"] = json_data.Serialize();
            object["position"] = picojson::value((double)position);

            return value;
        }

    private:
        Chat json_data;
        char position;
    };
} //ProtocolCraft