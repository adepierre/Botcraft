#if PROTOCOL_VERSION < 755 /* < 1.17 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerCombatPacket : public BaseMessage<ClientboundPlayerCombatPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x2D;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x2F;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x32;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x33;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x32;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x31;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Player Combat";

        DECLARE_FIELDS(
            (VarInt, VarInt, int, VarInt, Chat),
            (Event, Duration, KillerId, PlayerId, Message)
        );

        GETTER_SETTER(Event);
        GETTER_SETTER(Duration);
        GETTER_SETTER(KillerId);
        GETTER_SETTER(PlayerId);
        GETTER_SETTER(Message);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetEvent(ReadData<VarInt>(iter, length));

            if (GetEvent() == 1)
            {
                SetDuration(ReadData<VarInt>(iter, length));
                SetKillerId(ReadData<int>(iter, length));
            }
            else if (GetEvent() == 2)
            {
                SetPlayerId(ReadData<VarInt>(iter, length));
                SetKillerId(ReadData<int>(iter, length));
                SetMessage(ReadData<Chat>(iter, length));
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetEvent(), container);
            if (GetEvent() == 1)
            {
                WriteData<VarInt>(GetDuration(), container);
                WriteData<int>(GetKillerId(), container);
            }
            else if (GetEvent() == 2)
            {
                WriteData<VarInt>(GetPlayerId(), container);
                WriteData<int>(GetKillerId(), container);
                WriteData<Chat>(GetMessage(), container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Event)])] = GetEvent();
            if (GetEvent() == 1)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Duration)])] = GetDuration();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::KillerId)])] = GetKillerId();
            }
            else if (GetEvent() == 2)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::PlayerId)])] = GetPlayerId();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::KillerId)])] = GetKillerId();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Message)])] = GetMessage();
            }

            return output;
        }
    };
} //ProtocolCraft
#endif
