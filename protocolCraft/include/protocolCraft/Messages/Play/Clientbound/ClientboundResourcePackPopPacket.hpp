#pragma once

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundResourcePackPopPacket : public BaseMessage<ClientboundResourcePackPopPacket>
    {
    public:
#if   PROTOCOL_VERSION == 765 /* 1.20.3 */
        static constexpr int packet_id = 0x43;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Ressource Pack Pop";

        virtual ~ClientboundResourcePackPopPacket() override
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
