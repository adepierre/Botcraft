#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundLevelEventPacket : public BaseMessage<ClientboundLevelEventPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x21;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x21;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x21;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x25;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Level Event";

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


        int GetType() const
        {
            return type;
        }

        const NetworkPosition& GetPos() const
        {
            return pos;
        }

        int GetData() const
        {
            return data;
        }

        bool GetGlobalEvent() const
        {
            return global_event;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            type = ReadData<int>(iter, length);
            pos = ReadData<NetworkPosition>(iter, length);
            data = ReadData<int>(iter, length);
            global_event = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<int>(type, container);
            WriteData<NetworkPosition>(pos, container);
            WriteData<int>(data, container);
            WriteData<bool>(global_event, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["type"] = type;
            output["pos"] = pos;
            output["data"] = data;
            output["global_event"] = global_event;

            return output;
        }

    private:
        int type = 0;
        NetworkPosition pos;
        int data = 0;
        bool global_event = false;

    };
} //ProtocolCraft
