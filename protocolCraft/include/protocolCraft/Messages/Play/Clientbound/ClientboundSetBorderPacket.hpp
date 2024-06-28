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

        DECLARE_CONDITION(SetLerpInit, GetAction() == SetBorderType::SetSize || GetAction() == SetBorderType::LerpSize || GetAction() == SetBorderType::Initialize);
        DECLARE_CONDITION(LerpInit, GetAction() == SetBorderType::LerpSize || GetAction() == SetBorderType::Initialize);
        DECLARE_CONDITION(CenterInit, GetAction() == SetBorderType::SetCenter || GetAction() == SetBorderType::Initialize);
        DECLARE_CONDITION(Init, GetAction() == SetBorderType::Initialize);
        DECLARE_CONDITION(InitWarnTime, GetAction() == SetBorderType::Initialize || GetAction() == SetBorderType::SetWarningTime);
        DECLARE_CONDITION(InitWarnBlock, GetAction() == SetBorderType::Initialize || GetAction() == SetBorderType::SetWarningBlocks);

        DECLARE_FIELDS(
            (Internal::DiffType<SetBorderType, VarInt>, Internal::Conditioned<double, &THIS::CenterInit>, Internal::Conditioned<double, &THIS::CenterInit>, Internal::Conditioned<double, &THIS::LerpInit>, Internal::Conditioned<double, &THIS::SetLerpInit>, Internal::Conditioned<VarLong, &THIS::LerpInit>, Internal::Conditioned<VarInt, &THIS::Init>, Internal::Conditioned<VarInt, &THIS::InitWarnTime>, Internal::Conditioned<VarInt, &THIS::InitWarnBlock>),
            (Action,                                    NewCenterX,                                       NewCenterZ,                                       OldSize,                                        NewSize,                                           LerpTime,                                        NewAbsoluteMaxSize,                         WarningTime,                                        WarningBlocks)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Action);
        GETTER_SETTER(NewSize);
        GETTER_SETTER(OldSize);
        GETTER_SETTER(LerpTime);
        GETTER_SETTER(NewCenterX);
        GETTER_SETTER(NewCenterZ);
        GETTER_SETTER(NewAbsoluteMaxSize);
        GETTER_SETTER(WarningTime);
        GETTER_SETTER(WarningBlocks);
    };
} //ProtocolCraft
#endif
