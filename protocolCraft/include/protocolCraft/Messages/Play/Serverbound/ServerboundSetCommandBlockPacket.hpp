#pragma once

#if PROTOCOL_VERSION > 385
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundSetCommandBlockPacket : public BaseMessage<ServerboundSetCommandBlockPacket>
    {
    public:
#if   PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498 || PROTOCOL_VERSION == 573 ||  \
      PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736
        static constexpr int packet_id = 0x25;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754 || PROTOCOL_VERSION == 755 ||  \
      PROTOCOL_VERSION == 756 || PROTOCOL_VERSION == 757 ||  \
      PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x26;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x28;
#elif PROTOCOL_VERSION == 760 || PROTOCOL_VERSION == 761 ||  \
      PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x29;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Command Block";

        virtual ~ServerboundSetCommandBlockPacket() override
        {

        }

        void SetPos(const NetworkPosition& pos_)
        {
            pos = pos_;
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


        const NetworkPosition& GetPos() const
        {
            return pos;
        }

        const std::string& GetCommand() const
        {
            return command;
        }

        int GetMode() const
        {
            return mode;
        }

        char GetFlags() const
        {
            return flags;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            pos = ReadData<NetworkPosition>(iter, length);
            command = ReadData<std::string>(iter, length);
            mode = ReadData<VarInt>(iter, length);
            flags = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<NetworkPosition>(pos, container);
            WriteData<std::string>(command, container);
            WriteData<VarInt>(mode, container);
            WriteData<char>(flags, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["pos"] = pos;
            output["command"] = command;
            output["mode"] = mode;
            output["flags"] = flags;

            return output;
        }

    private:
        NetworkPosition pos;
        std::string command;
        int mode = 0;
        char flags = 0;

    };
} //ProtocolCraft
#endif
