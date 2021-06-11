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
#if PROTOCOL_VERSION == 755 // 1.17
            return 0x45;
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
            warning_delay = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(warning_delay, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["warning_delay"] = picojson::value((double)warning_delay);

            return value;
        }

    private:
        int warning_delay;

    };
} //ProtocolCraft
#endif