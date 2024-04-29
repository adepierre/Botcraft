#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundTakeItemEntityPacket : public BaseMessage<ClientboundTakeItemEntityPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x4B;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x4F;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x55;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x56;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x55;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */
        static constexpr int packet_id = 0x60;
#elif PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x61;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x62;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x65;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x63;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x67;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x6A;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x6C;
#elif PROTOCOL_VERSION == 766 /* 1.20.5 */
        static constexpr int packet_id = 0x6F;
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
