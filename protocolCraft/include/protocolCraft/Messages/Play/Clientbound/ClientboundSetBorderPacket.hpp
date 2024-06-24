#if PROTOCOL_VERSION < 755 /* < 1.17 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    enum class SetBorderType
    {
        SetSize = 0,
        LerpSize = 1,
        SetCenter = 2,
        Initialize = 3,
        SetWarningTime = 4,
        SetWarningBlocks = 5
    };

    class ClientboundSetBorderPacket : public BaseMessage<ClientboundSetBorderPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Border";

        DECLARE_FIELDS(
            (Internal::DiffType<SetBorderType, VarInt>, double,  double,  VarLong,  double,     double,     VarInt,             VarInt,      VarInt),
            (Action,                                    NewSize, OldSize, LerpTime, NewCenterX, NewCenterZ, NewAbsoluteMaxSize, WarningTime, WarningBlocks)
        );

        GETTER_SETTER(Action);
        GETTER_SETTER(NewSize);
        GETTER_SETTER(OldSize);
        GETTER_SETTER(LerpTime);
        GETTER_SETTER(NewCenterX);
        GETTER_SETTER(NewCenterZ);
        GETTER_SETTER(NewAbsoluteMaxSize);
        GETTER_SETTER(WarningTime);
        GETTER_SETTER(WarningBlocks);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetAction(ReadData<SetBorderType, VarInt>(iter, length));
            switch (GetAction())
            {
            case SetBorderType::SetSize:
                SetNewSize(ReadData<double>(iter, length));
                break;
            case SetBorderType::LerpSize:
                SetOldSize(ReadData<double>(iter, length));
                SetNewSize(ReadData<double>(iter, length));
                SetLerpTime(ReadData<VarLong>(iter, length));
                break;
            case SetBorderType::SetCenter:
                SetNewCenterX(ReadData<double>(iter, length));
                SetNewCenterZ(ReadData<double>(iter, length));
                break;
            case SetBorderType::Initialize:
                SetNewCenterX(ReadData<double>(iter, length));
                SetNewCenterZ(ReadData<double>(iter, length));
                SetOldSize(ReadData<double>(iter, length));
                SetNewSize(ReadData<double>(iter, length));
                SetLerpTime(ReadData<VarLong>(iter, length));
                SetNewAbsoluteMaxSize(ReadData<VarInt>(iter, length));
                SetWarningTime(ReadData<VarInt>(iter, length));
                SetWarningBlocks(ReadData<VarInt>(iter, length));
                break;
            case SetBorderType::SetWarningTime:
                SetWarningTime(ReadData<VarInt>(iter, length));
                break;
            case SetBorderType::SetWarningBlocks:
                SetWarningBlocks(ReadData<VarInt>(iter, length));
                break;
            default:
                break;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<SetBorderType, VarInt>(GetAction(), container);
            switch (GetAction())
            {
            case SetBorderType::SetSize:
                WriteData<double>(GetNewSize(), container);
                break;
            case SetBorderType::LerpSize:
                WriteData<double>(GetOldSize(), container);
                WriteData<double>(GetNewSize(), container);
                WriteData<VarLong>(GetLerpTime(), container);
                break;
            case SetBorderType::SetCenter:
                WriteData<double>(GetNewCenterX(), container);
                WriteData<double>(GetNewCenterZ(), container);
                break;
            case SetBorderType::Initialize:
                WriteData<double>(GetNewCenterX(), container);
                WriteData<double>(GetNewCenterZ(), container);
                WriteData<double>(GetOldSize(), container);
                WriteData<double>(GetNewSize(), container);
                WriteData<VarLong>(GetLerpTime(), container);
                WriteData<VarInt>(GetNewAbsoluteMaxSize(), container);
                WriteData<VarInt>(GetWarningTime(), container);
                WriteData<VarInt>(GetWarningBlocks(), container);
                break;
            case SetBorderType::SetWarningTime:
                WriteData<VarInt>(GetWarningTime(), container);
                break;
            case SetBorderType::SetWarningBlocks:
                WriteData<VarInt>(GetWarningBlocks(), container);
                break;
            default:
                break;
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Action)])] = GetAction();
            switch (GetAction())
            {
            case SetBorderType::SetSize:
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::NewSize)])] = GetNewSize();
                break;
            case SetBorderType::LerpSize:
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::OldSize)])] = GetOldSize();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::NewSize)])] = GetNewSize();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::LerpTime)])] = GetLerpTime();
                break;
            case SetBorderType::SetCenter:
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::NewCenterX)])] = GetNewCenterX();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::NewCenterZ)])] = GetNewCenterZ();
                break;
            case SetBorderType::Initialize:
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::NewCenterX)])] = GetNewCenterX();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::NewCenterZ)])] = GetNewCenterZ();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::OldSize)])] = GetOldSize();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::NewSize)])] = GetNewSize();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::LerpTime)])] = GetLerpTime();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::NewAbsoluteMaxSize)])] = GetNewAbsoluteMaxSize();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::WarningTime)])] = GetWarningTime();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::WarningBlocks)])] = GetWarningBlocks();
                break;
            case SetBorderType::SetWarningTime:
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::WarningTime)])] = GetWarningTime();
                break;
            case SetBorderType::SetWarningBlocks:
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::WarningBlocks)])] = GetWarningBlocks();
                break;
            default:
                break;
            }

            return output;
        }
    };
} //ProtocolCraft
#endif
