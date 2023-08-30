#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundTakeItemEntityPacket : public BaseMessage<ClientboundTakeItemEntityPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x4B;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x4F;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x55;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x56;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x55;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756
        static constexpr int packet_id = 0x60;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x61;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x62;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x65;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x63;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x67;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Take Item Entity";

        virtual ~ClientboundTakeItemEntityPacket() override
        {

        }

        void SetItemId(const int item_id_)
        {
            item_id = item_id_;
        }

        void SetPlayerId(const int player_id_)
        {
            player_id = player_id_;
        }

        void SetAmount(const int amount_)
        {
            amount = amount_;
        }


        int GetItemId() const
        {
            return item_id;
        }

        int GetPlayerId() const
        {
            return player_id;
        }

        int GetAmount() const
        {
            return amount;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            item_id = ReadData<VarInt>(iter, length);
            player_id = ReadData<VarInt>(iter, length);
            amount = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(item_id, container);
            WriteData<VarInt>(player_id, container);
            WriteData<VarInt>(amount, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["item_id"] = item_id;
            output["player_id"] = player_id;
            output["amount"] = amount;

            return output;
        }

    private:
        int item_id = 0;
        int player_id = 0;
        int amount = 0;

    };
} //ProtocolCraft
