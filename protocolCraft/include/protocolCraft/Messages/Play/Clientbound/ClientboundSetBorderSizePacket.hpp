#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderSizePacket : public BaseMessage<ClientboundSetBorderSizePacket>
    {
    public:
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x44;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x44;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x43;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x46;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x45;
#elif PROTOCOL_VERSION == 762 // 1.19.4
static constexpr int packet_id = 0x49;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Set Border Size";

        virtual ~ClientboundSetBorderSizePacket() override
        {

        }


        void SetSize(const double size_)
        {
            size = size_;
        }


        double GetSize() const
        {
            return size;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            size = ReadData<double>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<double>(size, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["size"] = size;

            return output;
        }

    private:
        double size;

    };
} //ProtocolCraft
#endif
