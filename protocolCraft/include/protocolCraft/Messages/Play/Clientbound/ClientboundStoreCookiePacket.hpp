#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ClientboundStoreCookiePacket : public BaseMessage<ClientboundStoreCookiePacket>
    {
    public:
#if   PROTOCOL_VERSION == 766 /* 1.20.5 */
        static constexpr int packet_id = 0x6B;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Store Cookie";

        virtual ~ClientboundStoreCookiePacket() override
        {

        }


        void SetKey(const Identifier& key_)
        {
            key = key_;
        }

        void SetPayload(const std::vector<unsigned char>& payload_)
        {
            payload = payload_;
        }


        const Identifier& GetKey() const
        {
            return key;
        }

        const std::vector<unsigned char>& GetPayload() const
        {
            return payload;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            key = ReadData<Identifier>(iter, length);
            payload = ReadByteArray(iter, length, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Identifier>(key, container);
            WriteByteArray(payload, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["key"] = key;
            output["payload"] = "vector of " + std::to_string(payload.size()) + " unsigned char";

            return output;
        }

    private:
        Identifier key;
        std::vector<unsigned char> payload;
    };
}
#endif
