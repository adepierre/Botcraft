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
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x10;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x10;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x0D;
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

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["reset_times"] = reset_times;

            return output;
    }

    private:
        bool reset_times;

    };
} //ProtocolCraft
#endif