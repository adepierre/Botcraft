#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundLoginDisconnectPacket : public BaseMessage<ClientboundLoginDisconnectPacket>
    {
    public:
        static constexpr int packet_id = 0x00;
        static constexpr std::string_view packet_name = "Login Disconnect";

        virtual ~ClientboundLoginDisconnectPacket() override
        {

        }

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        void SetReason(const Chat& reason_)
        {
            reason = reason_;
        }
#else
        void SetReason(const std::string& reason_)
        {
            reason = reason_;
        }
#endif

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        const Chat& GetReason() const
        {
            return reason;
        }
#else
        const std::string& GetReason() const
        {
            return reason;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
            reason = ReadData<Chat>(iter, length);
#else
            reason = ReadData<std::string>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
            WriteData<Chat>(reason, container);
#else
            WriteData<std::string>(reason, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["reason"] = reason;

            return output;
        }

    private:
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        Chat reason;
#else
        std::string reason;
#endif
    };
}
