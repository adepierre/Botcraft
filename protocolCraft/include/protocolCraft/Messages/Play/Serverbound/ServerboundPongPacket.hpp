#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPongPacket : public BaseMessage<ServerboundPongPacket>
    {
    public:
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 763 // 1.20
        static constexpr int packet_id = 0x20;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Pong";

        virtual ~ServerboundPongPacket() override
        {

        }

        void SetId_(const int id__)
        {
            id_ = id__;
        }


        int GetId_() const
        {
            return id_;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<int>(id_, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["id"] = id_;

            return output;
        }

    private:
        int id_ = 0;

    };
} //ProtocolCraft
#endif
