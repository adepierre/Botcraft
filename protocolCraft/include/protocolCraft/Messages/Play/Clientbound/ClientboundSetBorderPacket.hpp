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

        DEFINE_CONDITION(SetLerpInit, GetAction() == SetBorderType::SetSize || GetAction() == SetBorderType::LerpSize || GetAction() == SetBorderType::Initialize);
        DEFINE_CONDITION(LerpInit, GetAction() == SetBorderType::LerpSize || GetAction() == SetBorderType::Initialize);
        DEFINE_CONDITION(CenterInit, GetAction() == SetBorderType::SetCenter || GetAction() == SetBorderType::Initialize);
        DEFINE_CONDITION(Init, GetAction() == SetBorderType::Initialize);
        DEFINE_CONDITION(InitWarnTime, GetAction() == SetBorderType::Initialize || GetAction() == SetBorderType::SetWarningTime);
        DEFINE_CONDITION(InitWarnBlock, GetAction() == SetBorderType::Initialize || GetAction() == SetBorderType::SetWarningBlocks);

        SERIALIZED_FIELD(Action, Internal::DiffType<SetBorderType, VarInt>);
        SERIALIZED_FIELD(NewCenterX, Internal::Conditioned<double, &THIS::CenterInit>);
        SERIALIZED_FIELD(NewCenterZ, Internal::Conditioned<double, &THIS::CenterInit>);
        SERIALIZED_FIELD(OldSize, Internal::Conditioned<double, &THIS::LerpInit>);
        SERIALIZED_FIELD(NewSize, Internal::Conditioned<double, &THIS::SetLerpInit>);
        SERIALIZED_FIELD(LerpTime, Internal::Conditioned<VarLong, &THIS::LerpInit>);
        SERIALIZED_FIELD(NewAbsoluteMaxSize, Internal::Conditioned<VarInt, &THIS::Init>);
        SERIALIZED_FIELD(WarningTime, Internal::Conditioned<VarInt, &THIS::InitWarnTime>);
        SERIALIZED_FIELD(WarningBlocks, Internal::Conditioned<VarInt, &THIS::InitWarnBlock>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
