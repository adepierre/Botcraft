#pragma once

#if PROTOCOL_VERSION > 388
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundBlockEntityTagQuery : public BaseMessage<ServerboundBlockEntityTagQuery>
    {
    public:
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x01;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x01;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x01;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x01;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x01;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x01;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x01E;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x01;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x01;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x01;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x01;
#elif PROTOCOL_VERSION == 763 // 1.20
        static constexpr int packet_id = 0x01;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Block Entity Tag Query";

        virtual ~ServerboundBlockEntityTagQuery() override
        {

        }

        void SetTransactionId(const int transaction_id_)
        {
            transaction_id = transaction_id_;
        }

        void SetPos(const NetworkPosition& pos_)
        {
            pos = pos_;
        }


        int GetTransactionId() const
        {
            return transaction_id;
        }

        const NetworkPosition& GetPos() const
        {
            return pos;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            transaction_id = ReadData<VarInt>(iter, length);
            pos = ReadData<NetworkPosition>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(transaction_id, container);
            WriteData<NetworkPosition>(pos, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["transaction_id"] = transaction_id;
            output["pos"] = pos;

            return output;
        }

    private:
        int transaction_id = 0;
        NetworkPosition pos;

    };
} //ProtocolCraft
#endif
