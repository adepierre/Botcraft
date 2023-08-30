#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPlayerCommandPacket : public BaseMessage<ServerboundPlayerCommandPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498 || PROTOCOL_VERSION == 573 ||  \
      PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x1E;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Player Command";

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


        int GetId_() const
        {
            return id_;
        }

        int GetAction() const
        {
            return action;
        }

        int GetData() const
        {
            return data;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadData<VarInt>(iter, length);
            action = ReadData<VarInt>(iter, length);
            data = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(id_, container);
            WriteData<VarInt>(action, container);
            WriteData<VarInt>(data, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["id_"] = id_;
            output["action"] = action;
            output["data"] = data;

            return output;
        }

    private:
        int id_ = 0;
        int action = 0;
        int data = 0;

    };
} //ProtocolCraft
