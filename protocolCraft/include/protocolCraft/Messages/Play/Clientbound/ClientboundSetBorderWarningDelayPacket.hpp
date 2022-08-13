#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderWarningDelayPacket : public BaseMessage<ClientboundSetBorderWarningDelayPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x45;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x45;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x44;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x47;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Border Warning Delay";
        }

        virtual ~ClientboundSetBorderWarningDelayPacket() override
        {

        }


        void SetWarningDelay(const int warning_delay_)
        {
            warning_delay = warning_delay_;
        }


        const int GetWarningDelay() const
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

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["warning_delay"] = warning_delay;

            return output;
        }

    private:
        int warning_delay;

    };
} //ProtocolCraft
#endif