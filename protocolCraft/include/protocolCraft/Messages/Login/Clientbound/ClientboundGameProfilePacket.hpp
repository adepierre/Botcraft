#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundGameProfilePacket : public BaseMessage<ClientboundGameProfilePacket>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x02;
        }

        virtual const std::string GetName() const override
        {
            return "Game Profile";
        }

        virtual ~ClientboundGameProfilePacket() override
        {

        }

#if PROTOCOL_VERSION > 706
        void SetUUID(const UUID& uuid_)
        {
            uuid = uuid_;
        }
#else
        void SetUUID(const std::string& uuid_)
        {
            uuid = uuid_;
        }
#endif

        void SetUsername(const std::string& username_)
        {
            username = username_;
        }

#if PROTOCOL_VERSION > 706
        const UUID& GetUUID() const
        {
            return uuid;
        }
#else
        const std::string& GetUUID() const
        {
            return uuid;
        }
#endif

        const std::string& GetUsername() const
        {
            return username;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
#if PROTOCOL_VERSION > 706
            uuid = ReadData<UUID>(iter, length);
#else
            uuid = ReadData<std::string>(iter, length);
#endif
            username = ReadData<std::string>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
#if PROTOCOL_VERSION > 706
            WriteData<UUID>(uuid, container);
#else
            WriteData<std::string>(uuid, container);
#endif
            WriteData<std::string>(username, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["uuid"] = uuid;
            output["username"] = username;

            return output;
        }

    private:
#if PROTOCOL_VERSION > 706
        UUID uuid;
#else
        // This uuid is not a normal uuid but a regular string
        std::string uuid;
#endif
        std::string username;
    };
} //ProtocolCraft