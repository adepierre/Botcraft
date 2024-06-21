#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundBossEventPacket : public BaseMessage<ClientboundBossEventPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Boss Event";

        DECLARE_FIELDS(
            (UUID, VarInt,    Chat,  float, VarInt, VarInt,  unsigned char),
            (Id_,  Operation, Name_, Pct,   Color,  Overlay, Flags)
        );

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
