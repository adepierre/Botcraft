#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundCookieRequestConfigurationPacket : public BaseMessage<ClientboundCookieRequestConfigurationPacket>
    {
    public:
        static constexpr int packet_id = 0x00;
        static constexpr std::string_view packet_name = "Cookie Request (Configuration)";

        virtual ~ClientboundCookieRequestConfigurationPacket() override
        {

        }


        void SetKey(const Identifier& key_)
        {
            key = key_;
        }


        const Identifier& GetKey() const
        {
            return key;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            key = ReadData<Identifier>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Identifier>(key, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["key"] = key;

            return output;
        }

    private:
        Identifier key;
    };
}
#endif
