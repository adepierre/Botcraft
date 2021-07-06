#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPlayerCommandPacket : public BaseMessage<ServerboundPlayerCommandPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x15;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x19;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1B;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x1B;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x1C;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x1C;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x1B;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Command";
        }

        virtual ~ServerboundPlayerCommandPacket() override
        {

        }

        void SetId_(const int id__)
        {
            id_ = id__;
        }

        void SetAction(const int action_)
        {
            action = action_;
        }

        void SetData(const int data_)
        {
            data = data_;
        }


        const int GetId_() const
        {
            return id_;
        }

        const int GetAction() const
        {
            return action;
        }

        const int GetData() const
        {
            return data;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadVarInt(iter, length);
            action = ReadVarInt(iter, length);
            data = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(id_, container);
            WriteVarInt(action, container);
            WriteVarInt(data, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["id_"] = picojson::value((double)id_);
            object["action"] = picojson::value((double)action);
            object["data"] = picojson::value((double)data);

            return value;
        }

    private:
        int id_;
        int action;
        int data;

    };
} //ProtocolCraft