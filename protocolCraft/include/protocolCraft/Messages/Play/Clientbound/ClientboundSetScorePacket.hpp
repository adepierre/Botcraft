#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    enum class SetScoreMethod
    {
        Change = 0,
        Remove = 1
    };

    class ClientboundSetScorePacket : public BaseMessage<ClientboundSetScorePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Score";

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        DECLARE_FIELDS(
            (std::string, Internal::DiffType<SetScoreMethod, char>, std::string,   VarInt),
            (Owner,       Method,                                   ObjectiveName, Score)
        );
#else
        DECLARE_FIELDS(
            (std::string, std::string,   VarInt, std::optional<Chat>, std::optional<NumberFormat>),
            (Owner,       ObjectiveName, Score,  Display,             NumberFormat)
        );
        DECLARE_READ_WRITE_SERIALIZE;
#endif

        GETTER_SETTER(Owner);
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        GETTER_SETTER(Method);
#endif
        GETTER_SETTER(ObjectiveName);
        GETTER_SETTER(Score);
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        GETTER_SETTER(Display);
        GETTER_SETTER(NumberFormat);
#endif

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetOwner(ReadData<std::string>(iter, length));
            SetMethod(ReadData<SetScoreMethod, char>(iter, length));
            SetObjectiveName(ReadData<std::string>(iter, length));
            if (GetMethod() != SetScoreMethod::Remove)
            {
                SetScore(ReadData<VarInt>(iter, length));
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(GetOwner(), container);
            WriteData<SetScoreMethod, char>(GetMethod(), container);
            WriteData<std::string>(GetObjectiveName(), container);
            if (GetMethod() != SetScoreMethod::Remove)
            {
                WriteData<VarInt>(GetScore(), container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Owner)])] = GetOwner();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::ObjectiveName)])] = GetObjectiveName();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Method)])] = GetMethod();
            if (GetMethod() != SetScoreMethod::Remove)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Score)])] = GetScore();
            }

            return output;
        }
#endif
    };
} //ProtocolCraft
