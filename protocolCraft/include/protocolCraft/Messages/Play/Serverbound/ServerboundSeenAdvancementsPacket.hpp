#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ServerboundSeenAdvancementsPacket : public BaseMessage<ServerboundSeenAdvancementsPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Seen Advancement";

        DECLARE_FIELDS(
            (VarInt, Identifier),
            (Action, Tab)
        );

        GETTER_SETTER(Action);
        GETTER_SETTER(Tab);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetAction(ReadData<VarInt>(iter, length));
            if (GetAction() == 0)
            {
                SetTab(ReadData<Identifier>(iter, length));
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetAction(), container);
            if (GetAction() == 0)
            {
                WriteData<Identifier>(GetTab(), container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Action)])] = GetAction();
            if (GetAction() == 0)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Tab)])] = GetTab();
            }

            return output;
        }
    };
} //ProtocolCraft
