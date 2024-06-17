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
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x38;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x3B;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x3D;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x3E;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x3D;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Border";

        DECLARE_FIELDS(
            (DiffType<SetBorderType, VarInt>, double,  double,  VarLong,  double,     double,     VarInt,             VarInt,      VarInt),
            (Action,                          NewSize, OldSize, LerpTime, NewCenterX, NewCenterZ, NewAbsoluteMaxSize, WarningTime, WarningBlocks)
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
