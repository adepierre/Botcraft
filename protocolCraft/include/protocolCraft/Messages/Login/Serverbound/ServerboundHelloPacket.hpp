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

        void SetHasPublicKey(const bool has_public_key_)
        {
            has_public_key = has_public_key_;
        }

        void SetPublicKey(const ProfilePublicKey& public_key_)
        {
            public_key = public_key_;
        }

        const std::string& GetName_() const
        {
            return name_;
        }

        const bool GetHasPublicKey() const
        {
            return has_public_key;
        }

        const ProfilePublicKey& GetPublicKey() const
        {
            return public_key;
        }
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
            has_public_key = ReadData<bool>(iter, length);
            if (has_public_key)
            {
                public_key.Read(iter, length);
            }
#else
            game_profile = ReadData<std::string>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
#if PROTOCOL_VERSION > 758
            WriteData<std::string>(name_, container);
            WriteData<bool>(has_public_key, container);
            if (has_public_key)
            {
                public_key.Write(container);
            }
#else
            WriteData<std::string>(game_profile, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

#if PROTOCOL_VERSION > 758
            output["name"] = name_;
            if (has_public_key)
            {
                output["public_key"] = public_key.Serialize();
            }
#else
            output["game_profile"] = game_profile;
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION > 758
        std::string name_;
        bool has_public_key;
        ProfilePublicKey public_key;
#else
        std::string game_profile;
#endif
    };
} // Botcraft
