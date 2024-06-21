#if PROTOCOL_VERSION > 351 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerLookAtPacket : public BaseMessage<ClientboundPlayerLookAtPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Face Player";

        DECLARE_FIELDS(
            (VarInt,     double, double, double, bool,     VarInt, VarInt),
            (FromAnchor, X,      Y,      Z,      AtEntity, Entity, ToAnchor)
        );

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
