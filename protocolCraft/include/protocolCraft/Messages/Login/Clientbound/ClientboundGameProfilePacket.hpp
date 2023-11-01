#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/GameProfile/GameProfile.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundGameProfilePacket : public BaseMessage<ClientboundGameProfilePacket>
    {
    public:
        static constexpr int packet_id = 0x02;
        static constexpr std::string_view packet_name = "Game Profile";

        virtual ~ClientboundGameProfilePacket() override
        {

        }

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        void SetGameProfile(const GameProfile& game_profile_)
        {
            game_profile = game_profile_;
        }


        const GameProfile& GetGameProfile() const
        {
            return game_profile;
        }
#else
#if PROTOCOL_VERSION > 706 /* > 1.15.2 */
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

#if PROTOCOL_VERSION > 706 /* > 1.15.2 */
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
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            game_profile = ReadData<GameProfile>(iter, length);
#else
#if PROTOCOL_VERSION > 706 /* > 1.15.2 */
            uuid = ReadData<UUID>(iter, length);
#else
            uuid = ReadData<std::string>(iter, length);
#endif
            username = ReadData<std::string>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            WriteData<GameProfile>(game_profile, container);
#else
#if PROTOCOL_VERSION > 706 /* > 1.15.2 */
            WriteData<UUID>(uuid, container);
#else
            WriteData<std::string>(uuid, container);
#endif
            WriteData<std::string>(username, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            output["game_profile"] = game_profile;
#else
            output["uuid"] = uuid;
            output["username"] = username;
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        GameProfile game_profile;
#else
#if PROTOCOL_VERSION > 706 /* > 1.15.2 */
        UUID uuid = {};
#else
        // This uuid is not a normal uuid but a regular string
        std::string uuid;
#endif
        std::string username;
#endif
    };
} //ProtocolCraft
