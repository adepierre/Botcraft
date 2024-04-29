#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <optional>
#include <vector>

namespace ProtocolCraft
{
    class ServerboundCookieResponsePacket : public BaseMessage<ServerboundCookieResponsePacket>
    {
    public:
#if   PROTOCOL_VERSION == 766 /* 1.20.5 */
        static constexpr int packet_id = 0x11;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Cookie Response";

        virtual ~ServerboundCookieResponsePacket() override
        {

        }

        void SetKey(const Identifier& key_)
        {
            key = key_;
        }

        void SetPayload(const std::optional<std::vector<unsigned char>>& payload_)
        {
            payload = payload_;
        }


        const Identifier& GetKey() const
        {
            return key;
        }

        const std::optional<std::vector<unsigned char>>& GetPayload() const
        {
            return payload;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            key = ReadData<Identifier>(iter, length);
            payload = ReadOptional<std::vector<unsigned char>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadByteArray(i, l, l);
                }
            );
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Identifier>(key, container);
            WriteOptional<std::vector<unsigned char>>(payload, container,
                [](const std::vector<unsigned char>& v, WriteContainer& c)
                {
                    WriteByteArray(v, c);
                });
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["key"] = key;
            if (payload.has_value())
            {
                output["payload"] = "vector of " + std::to_string(payload.value().size()) + " unsigned char";
            }

            return output;
        }

    private:
        Identifier key;
        std::optional<std::vector<unsigned char>> payload;
    };
} // ProtocolCraft
#endif
