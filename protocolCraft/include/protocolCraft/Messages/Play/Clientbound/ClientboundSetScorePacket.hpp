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
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x45;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x48;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x4C;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */ || PROTOCOL_VERSION == 735 /* 1.16 */ ||  \
      PROTOCOL_VERSION == 736 /* 1.16.1 */ || PROTOCOL_VERSION == 751 /* 1.16.2 */ ||  \
      PROTOCOL_VERSION == 753 /* 1.16.3 */ || PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x4D;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */ ||  \
      PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x56;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x59;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x57;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x5B;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x5D;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x5F;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x61;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Score";

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        DECLARE_FIELDS_TYPES(std::string, DiffType<SetScoreMethod, char>, std::string,   VarInt);
        DECLARE_FIELDS_NAMES(Owner,       Method,                         ObjectiveName, Score);
#else
        DECLARE_FIELDS_TYPES(std::string, std::string,   VarInt, std::optional<Chat>, std::optional<NumberFormat>);
        DECLARE_FIELDS_NAMES(Owner,       ObjectiveName, Score,  Display,             NumberFormat);
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
