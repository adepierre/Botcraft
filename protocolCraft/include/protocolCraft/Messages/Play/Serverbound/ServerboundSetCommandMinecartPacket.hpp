#pragma once

#if PROTOCOL_VERSION > 385
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundSetCommandMinecartPacket : public BaseMessage<ServerboundSetCommandMinecartPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x23;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x25;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x25;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x26;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x27;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x27;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Command Minecart";
        }

        virtual ~ServerboundSetCommandMinecartPacket() override
        {

        }

        void SetEntity(const int entity_)
        {
            entity = entity_;
        }

        void SetCommand(const std::string& command_)
        {
            command = command_;
        }

        void SetTrackOutput(const bool track_output_)
        {
            track_output = track_output_;
        }


        const int GetEntity() const
        {
            return entity;
        }

        const std::string& GetCommand() const
        {
            return command;
        }

        const bool GetTrackOutput() const
        {
            return track_output;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity = ReadVarInt(iter, length);
            command = ReadData<std::string>(iter, length);
            track_output = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(entity, container);
            WriteData<std::string>(command, container);
            WriteData<bool>(track_output, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity"] = picojson::value((double)entity);
            object["command"] = picojson::value(command);
            object["track_output"] = picojson::value(track_output);

            return value;
        }

    private:
        int entity;
        std::string command;
        bool track_output;

    };
} //ProtocolCraft
#endif
