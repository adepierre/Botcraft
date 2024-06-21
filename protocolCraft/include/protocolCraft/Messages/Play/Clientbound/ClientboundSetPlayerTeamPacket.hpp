#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 374 /* > 1.12.2 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSetPlayerTeamPacket : public BaseMessage<ClientboundSetPlayerTeamPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Player Team";

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_FIELDS(
            (std::string, char,   std::string, std::string,  std::string,  char,    std::string,       std::string,   char,  std::vector<std::string>),
            (Name_,       Method, DisplayName, PlayerPrefix, PlayerSuffix, Options, NametagVisibility, CollisionRule, Color, Players)
        );
#else
        DECLARE_FIELDS(
            (std::string, char,   Chat,        char,    std::string,       std::string,   VarInt, Chat,        Chat,         std::vector<std::string>),
            (Name_,       Method, DisplayName, Options, NametagVisibility, CollisionRule, Color,  PlayerPrefix, PlayerSuffix, Players)
        );
#endif

        GETTER_SETTER(Name_);
        GETTER_SETTER(Method);
        GETTER_SETTER(DisplayName);
        GETTER_SETTER(PlayerPrefix);
        GETTER_SETTER(PlayerSuffix);
        GETTER_SETTER(Options);
        GETTER_SETTER(NametagVisibility);
        GETTER_SETTER(CollisionRule);
        GETTER_SETTER(Color);
        GETTER_SETTER(Players);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetName_(ReadData<std::string>(iter, length));
            SetMethod(ReadData<char>(iter, length));
            if (GetMethod() == 0 || GetMethod() == 2)
            {
#if PROTOCOL_VERSION < 375 /* < 1.13 */
                SetDisplayName(ReadData<std::string>(iter, length));
                SetPlayerPrefix(ReadData<std::string>(iter, length));
                SetPlayerSuffix(ReadData<std::string>(iter, length));
                SetOptions(ReadData<char>(iter, length));
                SetNametagVisibility(ReadData<std::string>(iter, length));
                SetCollisionRule(ReadData<std::string>(iter, length));
                SetColor(ReadData<char>(iter, length));
#else
                SetDisplayName(ReadData<Chat>(iter, length));
                SetOptions(ReadData<char>(iter, length));
                SetNametagVisibility(ReadData<std::string>(iter, length));
                SetCollisionRule(ReadData<std::string>(iter, length));
                SetColor(ReadData<VarInt>(iter, length));
                SetPlayerPrefix(ReadData<Chat>(iter, length));
                SetPlayerSuffix(ReadData<Chat>(iter, length));
#endif
            }

            if (GetMethod() == 0 || GetMethod() == 3 || GetMethod() == 4)
            {
                SetPlayers(ReadData<std::vector<std::string>>(iter, length));
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(GetName_(), container);
            WriteData<char>(GetMethod(), container);

            if (GetMethod() == 0 || GetMethod() == 2)
            {
#if PROTOCOL_VERSION < 375 /* < 1.13 */
                WriteData<std::string>(GetDisplayName(), container);
                WriteData<std::string>(GetPlayerPrefix(), container);
                WriteData<std::string>(GetPlayerSuffix(), container);
                WriteData<char>(GetOptions(), container);
                WriteData<std::string>(GetNametagVisibility(), container);
                WriteData<std::string>(GetCollisionRule(), container);
                WriteData<char>(GetColor(), container);
#else
                WriteData<Chat>(GetDisplayName(), container);
                WriteData<char>(GetOptions(), container);
                WriteData<std::string>(GetNametagVisibility(), container);
                WriteData<std::string>(GetCollisionRule(), container);
                WriteData<VarInt>(GetColor(), container);
                WriteData<Chat>(GetPlayerPrefix(), container);
                WriteData<Chat>(GetPlayerSuffix(), container);
#endif
            }

            if (GetMethod() == 0 || GetMethod() == 3 || GetMethod() == 4)
            {
                WriteData<std::vector<std::string>>(GetPlayers(), container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Name_)])] = GetName_();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Method)])] = GetMethod();

            if (GetMethod() == 0 || GetMethod() == 2)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::DisplayName)])] = GetDisplayName();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Options)])] = GetOptions();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::NametagVisibility)])] = GetNametagVisibility();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::CollisionRule)])] = GetCollisionRule();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Color)])] = GetColor();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::PlayerPrefix)])] = GetPlayerPrefix();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::PlayerSuffix)])] = GetPlayerSuffix();
            }

            if (GetMethod() == 0 || GetMethod() == 3 || GetMethod() == 4)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Players)])] = GetPlayers();
            }

            return output;
        }
    };
} //ProtocolCraft
