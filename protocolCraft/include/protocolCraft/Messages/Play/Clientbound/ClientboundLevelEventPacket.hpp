#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundLevelEventPacket : public BaseMessage<ClientboundLevelEventPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x21;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x23;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x22;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x23;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x22;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x21;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x23;
#elif PROTOCOL_VERSION == 757 // 1.18
            return 0x23;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Level Event";
        }

        virtual ~ClientboundLevelEventPacket() override
        {

        }

        void SetType(const int type_)
        {
            type = type_;
        }

        void SetPos(const NetworkPosition& pos_)
        {
            pos = pos_;
        }

        void SetData(const int data_)
        {
            data = data_;
        }

        void SetGlobalEvent(const bool global_event_)
        {
            global_event = global_event_;
        }


        const int GetType() const
        {
            return type;
        }

        const NetworkPosition& GetPos() const
        {
            return pos;
        }

        const int GetData() const
        {
            return data;
        }

        const bool GetGlobalEvent() const
        {
            return global_event;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            type = ReadData<int>(iter, length);
            pos.Read(iter, length);
            data = ReadData<int>(iter, length);
            global_event = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<int>(type, container);
            pos.Write(container);
            WriteData<int>(data, container);
            WriteData<bool>(global_event, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["type"] = type;
            output["pos"] = pos.Serialize();
            output["data"] = data;
            output["global_event"] = global_event;

            return output;
        }

    private:
        int type;
        NetworkPosition pos;
        int data;
        bool global_event;

    };
} //ProtocolCraft