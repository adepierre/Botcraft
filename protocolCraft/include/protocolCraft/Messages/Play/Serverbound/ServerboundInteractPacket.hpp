#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundInteractPacket : public BaseMessage<ServerboundInteractPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Interact";

#if PROTOCOL_VERSION < 735 /* < 1.16 */
        DECLARE_FIELDS(
            (VarInt,   VarInt, float,     float,     float,     VarInt),
            (EntityId, Action, LocationX, LocationY, LocationZ, Hand)
        );
#else
        DECLARE_FIELDS(
            (VarInt,   VarInt, float,     float,     float,     VarInt, bool),
            (EntityId, Action, LocationX, LocationY, LocationZ, Hand,   UsingSecondaryAction)
        );
#endif

        GETTER_SETTER(EntityId);
        GETTER_SETTER(Action);
        GETTER_SETTER(LocationX);
        GETTER_SETTER(LocationY);
        GETTER_SETTER(LocationZ);
        GETTER_SETTER(Hand);
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
        GETTER_SETTER(UsingSecondaryAction);
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetEntityId(ReadData<VarInt>(iter, length));
            SetAction(ReadData<VarInt>(iter, length));
            if (GetAction() == 2)
            {
                SetLocationX(ReadData<float>(iter, length));
                SetLocationY(ReadData<float>(iter, length));
                SetLocationZ(ReadData<float>(iter, length));
            }
            if (GetAction() == 0 || GetAction() == 2)
            {
                SetHand(ReadData<VarInt>(iter, length));
            }
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
            SetUsingSecondaryAction(ReadData<bool>(iter, length));
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetEntityId(), container);
            WriteData<VarInt>(GetAction(), container);
            if (GetAction() == 2)
            {
                WriteData<float>(GetLocationX(), container);
                WriteData<float>(GetLocationY(), container);
                WriteData<float>(GetLocationZ(), container);
            }
            if (GetAction() == 0 || GetAction() == 2)
            {
                WriteData<VarInt>(GetHand(), container);
            }
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
            WriteData<bool>(GetUsingSecondaryAction(), container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::EntityId)])] = GetEntityId();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Action)])] = GetAction();
            if (GetAction() == 2)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::LocationX)])] = GetLocationX();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::LocationY)])] = GetLocationY();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::LocationZ)])] = GetLocationZ();
            }
            if (GetAction() == 0 || GetAction() == 2)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Hand)])] = GetHand();
            }
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::UsingSecondaryAction)])] = GetUsingSecondaryAction();
#endif

            return output;
        }
    };
} //ProtocolCraft
