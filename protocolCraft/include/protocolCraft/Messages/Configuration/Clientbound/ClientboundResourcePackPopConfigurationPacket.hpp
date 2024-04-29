#pragma once

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundResourcePackPopConfigurationPacket : public BaseMessage<ClientboundResourcePackPopConfigurationPacket>
    {
    public:
#if   PROTOCOL_VERSION < 766 /* < 1.20.5 */
        static constexpr int packet_id = 0x06;
#elif PROTOCOL_VERSION == 766 /* 1.20.5 */
        static constexpr int packet_id = 0x08;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Resource Pack Pop (Configuration)";

        virtual ~ClientboundResourcePackPopConfigurationPacket() override
        {

        }

        void SetUUID(const std::optional<UUID>& uuid_)
        {
            uuid = uuid_;
        }


        const std::optional<UUID>& GetUUID() const
        {
            return uuid;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            uuid = ReadOptional<UUID>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteOptional<UUID>(uuid, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            if (uuid.has_value())
            {
                output["uuid"] = uuid.value();
            }

            return output;
        }

    private:
        std::optional<UUID> uuid;
    };
} //ProtocolCraft
#endif
