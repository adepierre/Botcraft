#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat.hpp"

namespace ProtocolCraft
{
    class DisconnectPlay : public BaseMessage<DisconnectPlay>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x1A;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x1B;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1A;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x1B;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x1A;
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x19;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Disconnect (play)";
        }

        void SetReason(const Chat& reason_)
        {
            reason = reason_;
        }

        const Chat& GetReason() const
        {
            return reason;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            reason.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            reason.Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = reason.Serialize();

            return value;
        }

    private:
        Chat reason;
    };
} //ProtocolCraft