#pragma once

#if PROTOCOL_VERSION < 755 //1.17
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerCombatPacket : public BaseMessage<ClientboundPlayerCombatPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x2D;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x2F;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x32;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x33;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x32;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x31;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Combat";
        }

        virtual ~ClientboundPlayerCombatPacket() override
        {

        }

        void SetEvent(const int event_)
        {
            event = event_;
        }

        void SetPlayerId(const int player_id_)
        {
            player_id = player_id_;
        }

        void SetKillerId(const int killer_id_)
        {
            killer_id = killer_id_;
        }

        void SetDuration(const int duration_)
        {
            duration = duration_;
        }

        void SetMessage(const Chat& message_)
        {
            message = message_;
        }


        const int GetEvent() const
        {
            return event;
        }

        const int GetPlayerId() const
        {
            return player_id;
        }

        const int GetKillerId() const
        {
            return killer_id;
        }

        const int GetDuration() const
        {
            return duration;
        }

        const Chat& GetMessage() const
        {
            return message;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            event = ReadData<VarInt>(iter, length);

            if (event == 1)
            {
                duration = ReadData<VarInt>(iter, length);
                killer_id = ReadData<int>(iter, length);
            }
            else if (event == 2)
            {
                player_id = ReadData<VarInt>(iter, length);
                killer_id = ReadData<int>(iter, length);
                message.Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(event, container);
            if (event == 1)
            {
                WriteData<VarInt>(duration, container);
                WriteData<int>(killer_id, container);
            }
            else if (event == 2)
            {
                WriteData<VarInt>(player_id, container);
                WriteData<int>(killer_id, container);
                message.Write(container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["event"] = picojson::value((double)event);
            if (event == 1)
            {
                object["duration"] = picojson::value((double)duration);
                object["killer_id"] = picojson::value((double)killer_id);
            }
            else if (event == 2)
            {
                object["player_id"] = picojson::value((double)player_id);
                object["killer_id"] = picojson::value((double)killer_id);
                object["message"] = message.Serialize();
            }

            return value;
        }

    private:
        int event;
        int player_id;
        int killer_id;
        int duration;
        Chat message;

    };
} //ProtocolCraft
#endif