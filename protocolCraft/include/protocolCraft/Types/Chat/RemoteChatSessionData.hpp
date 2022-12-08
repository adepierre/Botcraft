#if PROTOCOL_VERSION > 760
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/GameProfile/ProfilePublicKey.hpp"

namespace ProtocolCraft
{
    class RemoteChatSessionData : public NetworkType
    {
    public:
        virtual ~RemoteChatSessionData() override
        {

        }

        void SetUUID(const UUID& uuid_)
        {
            uuid = uuid_;
        }

        void SetProfilePublicKey(const ProfilePublicKey& profile_public_key_)
        {
            profile_public_key = profile_public_key_;
        }


        const UUID& GetUUID() const
        {
            return uuid;
        }

        const ProfilePublicKey& GetProfilePublicKey() const
        {
            return profile_public_key;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            uuid = ReadData<UUID>(iter, length);
            profile_public_key.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<UUID>(uuid, container);
            profile_public_key.Write(container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["uuid"] = uuid;
            output["profile_public_key"] = profile_public_key.Serialize();

            return output;
        }

    private:
        UUID uuid;
        ProfilePublicKey profile_public_key;
    };
}
#endif
