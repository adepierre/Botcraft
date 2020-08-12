#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 389
#include "protocolCraft/Types/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ScoreboardObjective : public BaseMessage<ScoreboardObjective>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x42;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x45;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x49;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x4A;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x4A;
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x4A;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Scoreboard Objective";
        }

        void SetObjectiveName(const std::string& objective_name_)
        {
            objective_name = objective_name_;
        }

        void SetMode(const char mode_)
        {
            mode = mode_;
        }

#if PROTOCOL_VERSION < 390
        void SetObjectiveValue(const std::string& objective_value_)
#else
        void SetObjectiveValue(const Chat& objective_value_)
#endif
        {
            objective_value = objective_value_;
        }

#if PROTOCOL_VERSION < 349
        void SetType(const std::string& type_)
#else
        void SetType(const int type_)
#endif
        {
            type = type_;
        }


        const std::string& GetObjectiveName() const
        {
            return objective_name;
        }

        const char GetMode() const
        {
            return mode;
        }

#if PROTOCOL_VERSION < 390
        const std::string& GetObjectiveValue() const
#else
        const Chat& GetObjectiveValue() const
#endif
        {
            return objective_value;
        }

#if PROTOCOL_VERSION < 349
        const std::string& GetType() const
#else
        const int GetType() const
#endif
        {
            return type;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            objective_name = ReadString(iter, length);
            mode = ReadData<char>(iter, length);
#if PROTOCOL_VERSION < 390
            objective_value = ReadString(iter, length);
#else
            objective_value.Read(iter, length);
#endif
#if PROTOCOL_VERSION < 349
            type = ReadString(iter, length);
#else
            type = ReadVarInt(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteString(objective_name, container);
            WriteData<char>(mode, container);
#if PROTOCOL_VERSION < 390
            WriteString(objective_value, container);
#else
            objective_value.Write(container);
#endif
#if PROTOCOL_VERSION < 349
            WriteString(type, container);
#else
            WriteVarInt(type, container);
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["objective_name"] = picojson::value(objective_name);
            object["mode"] = picojson::value((double)mode);
#if PROTOCOL_VERSION < 390
            object["objective_value"] = picojson::value(objective_value);
#else
            object["objective_value"] = objective_value.Serialize();
#endif
#if PROTOCOL_VERSION < 349
            object["type"] = picojson::value(type);
#else
            object["type"] = picojson::value((double)type);
#endif

            return value;
        }

    private:
        std::string objective_name;
        char mode;
#if PROTOCOL_VERSION < 390
        std::string objective_value;
#else
        Chat objective_value;
#endif
#if PROTOCOL_VERSION < 349
        std::string type;
#else
        int type;
#endif
    };
} //ProtocolCraft