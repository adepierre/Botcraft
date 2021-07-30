#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundTakeItemEntityPacket : public BaseMessage<ClientboundTakeItemEntityPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x4B;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x4F;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x55;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x56;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x55;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x55;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x60;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Take Item Entity";
        }

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


        const int GetItemId() const
        {
            return item_id;
        }

        const int GetPlayerId() const
        {
            return player_id;
        }

        const int GetAmount() const
        {
            return amount;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            item_id = ReadVarInt(iter, length);
            player_id = ReadVarInt(iter, length);
            amount = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(item_id, container);
            WriteVarInt(player_id, container);
            WriteVarInt(amount, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["item_id"] = picojson::value((double)item_id);
            object["player_id"] = picojson::value((double)player_id);
            object["amount"] = picojson::value((double)amount);

            return value;
        }

    private:
        int item_id;
        int player_id;
        int amount;

    };
} //ProtocolCraft