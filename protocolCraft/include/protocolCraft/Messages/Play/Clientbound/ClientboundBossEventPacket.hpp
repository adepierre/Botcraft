#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundBossEventPacket : public BaseMessage<ClientboundBossEventPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */ || PROTOCOL_VERSION == 393 /* 1.13 */ ||  \
      PROTOCOL_VERSION == 401 /* 1.13.1 */ || PROTOCOL_VERSION == 404 /* 1.13.2 */ ||  \
      PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 759 /* 1.19 */ || PROTOCOL_VERSION == 760 /* 1.19.1/2 */ ||  \
      PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x0A;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */ ||  \
      PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x0A;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Boss Event";

        DECLARE_FIELDS_TYPES(UUID, VarInt,    Chat,  float, VarInt, VarInt,  unsigned char);
        DECLARE_FIELDS_NAMES(Id_,  Operation, Name_, Pct,   Color,  Overlay, Flags);

        GETTER_SETTER(Id_);
        GETTER_SETTER(Operation);
        GETTER_SETTER(Name_);
        GETTER_SETTER(Pct);
        GETTER_SETTER(Color);
        GETTER_SETTER(Overlay);
        GETTER_SETTER(Flags);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetId_(ReadData<UUID>(iter, length));
            SetOperation(ReadData<VarInt>(iter, length));
            switch (GetOperation())
            {
            case 0:
                SetName_(ReadData<Chat>(iter, length));
                SetPct(ReadData<float>(iter, length));
                SetColor(ReadData<VarInt>(iter, length));
                SetOverlay(ReadData<VarInt>(iter, length));
                SetFlags(ReadData<unsigned char>(iter, length));
                break;
            case 1:
                break;
            case 2:
                SetPct(ReadData<float>(iter, length));
                break;
            case 3:
                SetName_(ReadData<Chat>(iter, length));
                break;
            case 4:
                SetColor(ReadData<VarInt>(iter, length));
                SetOverlay(ReadData<VarInt>(iter, length));
                break;
            case 5:
                SetFlags(ReadData<unsigned char>(iter, length));
                break;
            default:
                break;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<UUID>(GetId_(), container);
            WriteData<VarInt>(GetOperation(), container);
            switch (GetOperation())
            {
            case 0:
                WriteData<Chat>(GetName_(), container);
                WriteData<float>(GetPct(), container);
                WriteData<VarInt>(GetColor(), container);
                WriteData<VarInt>(GetOverlay(), container);
                WriteData<unsigned char>(GetFlags(), container);
                break;
            case 1:
                break;
            case 2:
                WriteData<float>(GetPct(), container);
                break;
            case 3:
                WriteData<Chat>(GetName_(), container);
                break;
            case 4:
                WriteData<VarInt>(GetColor(), container);
                WriteData<VarInt>(GetOverlay(), container);
                break;
            case 5:
                WriteData<unsigned char>(GetFlags(), container);
                break;
            default:
                break;
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Id_)])] = GetId_();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Operation)])] = GetOperation();

            switch (GetOperation())
            {
            case 0:
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Name_)])] = GetName_();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Pct)])] = GetPct();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Color)])] = GetColor();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Overlay)])] = GetOverlay();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Flags)])] = GetFlags();
                break;
            case 1:
                break;
            case 2:
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Pct)])] = GetPct();
                break;
            case 3:
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Name_)])] = GetName_();
                break;
            case 4:
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Color)])] = GetColor();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Overlay)])] = GetOverlay();
                break;
            case 5:
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Flags)])] = GetFlags();
                break;
            default:
                break;
            }

            return output;
        }
    };
} //ProtocolCraft
