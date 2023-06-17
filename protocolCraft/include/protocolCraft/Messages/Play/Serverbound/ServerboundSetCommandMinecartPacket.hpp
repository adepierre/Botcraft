#pragma once

#if PROTOCOL_VERSION > 385
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundSetCommandMinecartPacket : public BaseMessage<ServerboundSetCommandMinecartPacket>
    {
    public:
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x25;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x25;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x26;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x2A;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x2A;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x2A;
#elif PROTOCOL_VERSION == 763 // 1.20
        static constexpr int packet_id = 0x2A;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Set Command Minecart";

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


        int GetEntity() const
        {
            return entity;
        }

        const std::string& GetCommand() const
        {
            return command;
        }

        bool GetTrackOutput() const
        {
            return track_output;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity = ReadData<VarInt>(iter, length);
            command = ReadData<std::string>(iter, length);
            track_output = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(entity, container);
            WriteData<std::string>(command, container);
            WriteData<bool>(track_output, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["entity"] = entity;
            output["command"] = command;
            output["track_output"] = track_output;

            return output;
        }

    private:
        int entity = 0;
        std::string command;
        bool track_output = false;

    };
} //ProtocolCraft
#endif
