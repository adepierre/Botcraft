#if PROTOCOL_VERSION > 493 /* > 1.14.3 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundBlockBreakAckPacket : public BaseMessage<ClientboundBlockBreakAckPacket>
    {
    public:
#if   PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x5C;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x08;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Block Break Ack";

        virtual ~ClientboundBlockBreakAckPacket() override
        {

        }

        void SetPos(const NetworkPosition& pos_)
        {
            pos = pos_;
        }

        void SetState(const int state_)
        {
            state = state_;
        }

        void SetAction(const int action_)
        {
            action = action_;
        }

        void SetAllGood(const bool all_good_)
        {
            all_good = all_good_;
        }

        const NetworkPosition& GetPos() const
        {
            return pos;
        }

        int GetState() const
        {
            return state;
        }

        int GetAction() const
        {
            return action;
        }

        bool GetAllGood() const
        {
            return all_good;
        }
    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            pos = ReadData<NetworkPosition>(iter, length);
            state = ReadData<VarInt>(iter, length);
            action = ReadData<VarInt>(iter, length);
            all_good = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<NetworkPosition>(pos, container);
            WriteData<VarInt>(state, container);
            WriteData<VarInt>(action, container);
            WriteData<bool>(all_good, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["pos"] = pos;
            output["state"] = state;
            output["action"] = action;
            output["all_good"] = all_good;

            return output;
        }

    private:
        NetworkPosition pos;
        int state = 0;
        int action = 0;
        bool all_good = false;
    };
} //ProtocolCraft

#endif
