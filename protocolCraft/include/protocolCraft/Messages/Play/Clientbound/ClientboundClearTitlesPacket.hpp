#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundClearTitlesPacket : public BaseMessage<ClientboundClearTitlesPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 755 // 1.17
            return 0x10;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Clear Titles";
        }

        virtual ~ClientboundClearTitlesPacket() override
        {

        }

        void SetResetTimes(const bool reset_times_)
        {
            reset_times = reset_times_;
        }


        const bool GetResetTimes() const
        {
            return reset_times;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            reset_times = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<bool>(reset_times, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["reset_times"] = picojson::value((double)reset_times);

            return value;
    }

    private:
        bool reset_times;

    };
} //ProtocolCraft
#endif