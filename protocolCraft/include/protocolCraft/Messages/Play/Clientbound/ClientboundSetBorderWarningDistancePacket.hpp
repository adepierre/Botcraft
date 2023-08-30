#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderWarningDistancePacket : public BaseMessage<ClientboundSetBorderWarningDistancePacket>
    {
    public:
#if   PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x46;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x45;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x48;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x47;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x4B;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Border Warning Distance";

        virtual ~ClientboundSetBorderWarningDistancePacket() override
        {

        }


        void SetWarningBlocks(const int warning_blocks_)
        {
            warning_blocks = warning_blocks_;
        }


        int GetWarningBlocks() const
        {
            return warning_blocks;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            warning_blocks = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(warning_blocks, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["warning_blocks"] = warning_blocks;

            return output;
        }

    private:
        int warning_blocks = 0;

    };
} //ProtocolCraft
#endif
