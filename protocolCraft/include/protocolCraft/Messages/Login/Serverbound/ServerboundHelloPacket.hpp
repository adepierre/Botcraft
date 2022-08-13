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

        void SetPublicKey(const ProfilePublicKey& public_key_)
        {
            public_key = public_key_;
        }

#if PROTOCOL_VERSION > 759
        void SetProfileId(const UUID& profile_id_)
        {
            profile_id = profile_id_;
        }
#endif

        const std::string& GetName_() const
        {
            return name_;
        }

        const ProfilePublicKey& GetPublicKey() const
        {
            return public_key;
        }

#if PROTOCOL_VERSION > 759
        const UUID& GetProfileId() const
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
            const bool has_public_key = ReadData<bool>(iter, length);
            if (has_public_key)
            {
                public_key.Read(iter, length);
            }
#if PROTOCOL_VERSION > 759
            const bool has_profile_id = ReadData<bool>(iter, length);
            if (has_profile_id)
            {
                profile_id = ReadData<UUID>(iter, length);
            }
#endif
#else
            game_profile = ReadData<std::string>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
#if PROTOCOL_VERSION > 758
            WriteData<std::string>(name_, container);
            WriteData<bool>(!public_key.GetKey().empty(), container);
            if (!public_key.GetKey().empty())
            {
                public_key.Write(container);
            }
#if PROTOCOL_VERSION > 759
            bool has_profile_id = false;
            for (int i = 0; i < profile_id.size(); ++i)
            {
                if (profile_id[i] != 0)
                {
                    has_profile_id = true;
                    break;
                }
            }

            WriteData<bool>(has_profile_id, container);
            if (has_profile_id)
            {
                WriteData<UUID>(profile_id, container);
            }
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
            if (!public_key.GetKey().empty())
            {
                output["public_key"] = public_key.Serialize();
            }
#if PROTOCOL_VERSION > 759
            bool has_profile_id = false;
            for (int i = 0; i < profile_id.size(); ++i)
            {
                if (profile_id[i] != 0)
                {
                    has_profile_id = true;
                    break;
                }
            }
            if (has_profile_id)
            {
                output["profile_id"] = profile_id;
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
        ProfilePublicKey public_key;
#if PROTOCOL_VERSION > 759
        UUID profile_id;
#endif
#else
        std::string game_profile;
#endif
    };
} // Botcraft
