#pragma once

#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderWarningDelayPacket : public BaseMessage<ClientboundSetBorderWarningDelayPacket>
    {
    public:
#if   PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x45;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x44;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x47;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x46;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x4A;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x4C;
#elif PROTOCOL_VERSION == 765 /* 1.20.3 */
        static constexpr int packet_id = 0x4E;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Border Warning Delay";

        virtual ~ClientboundSetBorderWarningDelayPacket() override
        {

        }


        void SetWarningDelay(const int warning_delay_)
        {
            warning_delay = warning_delay_;
        }


        int GetWarningDelay() const
        {
            return warning_delay;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            warning_delay = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(warning_delay, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["warning_delay"] = warning_delay;

            return output;
        }

    private:
        int warning_delay = 0;

    };
} //ProtocolCraft
#endif
