#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundPlayerActionPacket : public BaseMessage<ServerboundPlayerActionPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x14;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x18;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1A;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x1A;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x1B;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x1B;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x1A;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Action";
        }

        virtual ~ServerboundPlayerActionPacket() override
        {

        }


        void SetPos(const NetworkPosition &pos_)
        {
            pos = pos_;
        }

        void SetDirection(const int direction_)
        {
            direction = direction_;
        }

        void SetAction(const int action_)
        {
            action = action_;
        }

        const NetworkPosition GetPos() const
        {
            return pos;
        }

        const int GetDirection() const
        {
            return direction;
        }

        const int GetAction() const
        {
            return action;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            action = ReadVarInt(iter, length);
            pos.Read(iter, length);
            direction = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVarInt(action, container);
            pos.Write(container);
            WriteData<char>(direction, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["pos"] = pos.Serialize();
            object["direction"] = picojson::value((double)direction);
            object["action"] = picojson::value((double)action);

            return value;
        }

    private:
        NetworkPosition pos;
        char direction;
        int action;
    };
} //ProtocolCraft