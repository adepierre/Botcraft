#pragma once

#if PROTOCOL_VERSION > 385
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class UpdateCommandBlock : public BaseMessage<UpdateCommandBlock>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x22;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x24;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x24;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
            return 0x25;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update Command Block";
        }

        void SetLocation(const NetworkPosition& location_)
        {
            location = location_;
        }

        void SetCommand(const std::string& command_)
        {
            command = command_;
        }

        void SetMode(const int mode_)
        {
            mode = mode_;
        }

        void SetFlags(const char flags_)
        {
            flags = flags_;
        }


        const NetworkPosition& GetLocation() const
        {
            return location;
        }

        const std::string& GetCommand() const
        {
            return command;
        }

        const int GetMode() const
        {
            return mode;
        }

        const char GetFlags() const
        {
            return flags;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            location.Read(iter, length);
            command = ReadString(iter, length);
            mode = ReadVarInt(iter, length);
            flags = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            location.Write(container);
            WriteString(command, container);
            WriteVarInt(mode, container);
            WriteData<char>(flags, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["location"] = location.Serialize();
            object["command"] = picojson::value(command);
            object["mode"] = picojson::value((double)mode);
            object["flags"] = picojson::value((double)flags);

            return value;
        }

    private:
        NetworkPosition location;
        std::string command;
        int mode;
        char flags;

    };
} //ProtocolCraft
#endif
