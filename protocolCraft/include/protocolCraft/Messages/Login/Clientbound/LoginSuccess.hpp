#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class LoginSuccess : public BaseMessage<LoginSuccess>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x02;
        }

        virtual const std::string GetName() const override
        {
            return "Login Success";
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
            uuid = ReadUUID(iter, length);
#else
            uuid = ReadString(iter, length);
#endif
            username = ReadString(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
#if PROTOCOL_VERSION > 706
            WriteUUID(uuid, container);
#else
            WriteString(uuid, container);
#endif
            WriteString(username, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["uuid"] = picojson::value(uuid);
            object["username"] = picojson::value(username);

            return value;
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