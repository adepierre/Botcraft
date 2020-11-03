#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class UpdateScore : public BaseMessage<UpdateScore>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x45;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x48;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x4C;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x4D;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x4D;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4
            return 0x4D;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update Score";
        }

        void SetEntityName(const std::string& entity_name_)
        {
            entity_name = entity_name_;
        }

        void SetAction(const char action_)
        {
            action = action_;
        }

        void SetObjectiveName(const std::string& objective_name_)
        {
            objective_name = objective_name_;
        }

        void SetValue(const int value_)
        {
            value = value_;
        }


        const std::string& GetEntityName() const
        {
            return entity_name;
        }

        const char GetAction() const
        {
            return action;
        }

        const std::string& GetObjectiveName() const
        {
            return objective_name;
        }

        const int GetValue() const
        {
            return value;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_name = ReadString(iter, length);
            action = ReadData<char>(iter, length);
            objective_name = ReadString(iter, length);
            if (action != 1)
            {
                value = ReadVarInt(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteString(entity_name, container);
            WriteData<char>(action, container);
            WriteString(objective_name, container);
            if (action != 1)
            {
                WriteVarInt(value, container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value val(picojson::object_type, false);
            picojson::object& object = val.get<picojson::object>();

            object["entity_name"] = picojson::value(entity_name);
            object["action"] = picojson::value((double)action);
            object["objective_name"] = picojson::value(objective_name);
            if (action != 1)
            {
                object["value"] = picojson::value((double)value);
            }

            return val;
        }

    private:
        std::string entity_name;
        char action;
        std::string objective_name;
        int value;

    };
} //ProtocolCraft