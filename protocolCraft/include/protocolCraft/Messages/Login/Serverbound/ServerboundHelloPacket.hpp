#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 758
#include "protocolCraft/Types/GameProfile/ProfilePublicKey.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundHelloPacket : public BaseMessage<ServerboundHelloPacket>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x00;
        }

        virtual const std::string GetName() const override
        {
            return "Hello";
        }

        virtual ~ServerboundHelloPacket() override
        {

        }

#if PROTOCOL_VERSION > 758
        void SetName(const std::string& name__)
        {
            name_ = name__;
        }

#if PROTOCOL_VERSION < 761
        void SetPublicKey(const std::optional<ProfilePublicKey>& public_key_)
        {
            public_key = public_key_;
        }
#endif

#if PROTOCOL_VERSION > 759
        void SetProfileId(const std::optional<UUID>& profile_id_)
        {
            profile_id = profile_id_;
        }
#endif

        const std::string& GetName_() const
        {
            return name_;
        }

#if PROTOCOL_VERSION < 761
        const std::optional<ProfilePublicKey>& GetPublicKey() const
        {
            return public_key;
        }
#endif

#if PROTOCOL_VERSION > 759
        const std::optional<UUID>& GetProfileId() const
        {
            return profile_id;
        }
#endif
#else
        void SetGameProfile(const std::string &n)
        {
            game_profile = n;
        }

        const std::string& GetGameProfile() const
        {
            return game_profile;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
#if PROTOCOL_VERSION > 758
            name_ = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION < 761
            public_key = ReadOptional<ProfilePublicKey>(iter, length);
#endif
#if PROTOCOL_VERSION > 759
            profile_id = ReadOptional<UUID>(iter, length);
#endif
#else
            game_profile = ReadData<std::string>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
#if PROTOCOL_VERSION > 758
            WriteData<std::string>(name_, container);
#if PROTOCOL_VERSION < 761
            WriteOptional<ProfilePublicKey>(public_key, container);
#endif
#if PROTOCOL_VERSION > 759
            WriteOptional<UUID>(profile_id, container);
#endif
#else
            WriteData<std::string>(game_profile, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

#if PROTOCOL_VERSION > 758
            output["name"] = name_;
#if PROTOCOL_VERSION < 761
            if (public_key.has_value())
            {
                output["public_key"] = public_key.value().Serialize();
            }
#endif
#if PROTOCOL_VERSION > 759
            if (profile_id.has_value())
            {
                output["profile_id"] = profile_id.value();
            }
#endif
#else
            output["game_profile"] = game_profile;
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION > 758
        std::string name_;
#if PROTOCOL_VERSION < 761
        std::optional<ProfilePublicKey> public_key;
#endif
#if PROTOCOL_VERSION > 759
        std::optional<UUID> profile_id;
#endif
#else
        std::string game_profile;
#endif
    };
} // ProtocolCraft
