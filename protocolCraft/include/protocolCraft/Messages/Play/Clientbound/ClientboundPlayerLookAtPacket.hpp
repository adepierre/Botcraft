#if PROTOCOL_VERSION > 351 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerLookAtPacket : public BaseMessage<ClientboundPlayerLookAtPacket>
    {
    public:
#if   PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x31;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x33;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x37;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x38;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x37;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x3B;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x3D;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x3F;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Face Player";

        DECLARE_FIELDS_TYPES(VarInt,     double, double, double, bool,     VarInt, VarInt);
        DECLARE_FIELDS_NAMES(FromAnchor, X,      Y,      Z,      AtEntity, Entity, ToAnchor);

        GETTER_SETTER(FromAnchor);
        GETTER_SETTER(X);
        GETTER_SETTER(Y);
        GETTER_SETTER(Z);
        GETTER_SETTER(AtEntity);
        GETTER_SETTER(Entity);
        GETTER_SETTER(ToAnchor);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetFromAnchor(ReadData<VarInt>(iter, length));
            SetX(ReadData<double>(iter, length));
            SetY(ReadData<double>(iter, length));
            SetZ(ReadData<double>(iter, length));
            SetAtEntity(ReadData<bool>(iter, length));
            if (GetAtEntity())
            {
                SetEntity(ReadData<VarInt>(iter, length));
                SetToAnchor(ReadData<VarInt>(iter, length));
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetFromAnchor(), container);
            WriteData<double>(GetX(), container);
            WriteData<double>(GetY(), container);
            WriteData<double>(GetZ(), container);
            WriteData<bool>(GetAtEntity(), container);
            if (GetAtEntity())
            {
                WriteData<VarInt>(GetEntity(), container);
                WriteData<VarInt>(GetToAnchor(), container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::FromAnchor)])] = GetFromAnchor();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::X)])] = GetX();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Y)])] = GetY();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Z)])] = GetZ();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::AtEntity)])] = GetAtEntity();
            if (GetAtEntity())
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Entity)])] = GetEntity();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::ToAnchor)])] = GetToAnchor();
            }

            return output;
        }
    };
} //ProtocolCraft
#endif
