#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundCommandSuggestionPacket : public BaseMessage<ServerboundCommandSuggestionPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x01;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x06;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x06;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x06;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x06;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x06;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x06;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x08;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Command Suggestion";

        virtual ~ServerboundCommandSuggestionPacket() override
        {

        }

#if PROTOCOL_VERSION > 344
        void SetId_(const int id__)
        {
            id_ = id__;
        }
#endif

        void SetCommand(const std::string& command_)
        {
            command = command_;
        }

#if PROTOCOL_VERSION < 345
        void SetAssumeCommand(const bool assume_command_)
        {
            assume_command = assume_command_;
        }

        void SetLookedAtBlock(const std::optional<NetworkPosition>& looked_at_block_)
        {
            looked_at_block = looked_at_block_;
        }
#endif


#if PROTOCOL_VERSION > 344
        int GetId_() const
        {
            return id_;
        }
#endif

        const std::string& GetCommand() const
        {
            return command;
        }

#if PROTOCOL_VERSION < 345
        bool GetAssumeCommand() const
        {
            return assume_command;
        }

        const std::optional<NetworkPosition>& GetLookedAtBlock() const
        {
            return looked_at_block;
        }
#endif



    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION > 344
            id_ = ReadData<VarInt>(iter, length);
#endif
            command = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION < 345
            assume_command = ReadData<bool>(iter, length);
            looked_at_block = ReadOptional<NetworkPosition>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION > 344
            WriteData<VarInt>(id_, container);
#endif
            WriteData<std::string>(command, container);
#if PROTOCOL_VERSION < 345
            WriteData<bool>(assume_command, container);
            WriteOptional<NetworkPosition>(looked_at_block, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION > 344
            output["id_"] = id_;
#endif
            output["command"] = command;
#if PROTOCOL_VERSION < 345
            output["assume_command"] = assume_command;
            if (looked_at_block.has_value())
            {
                output["looked_at_block"] = looked_at_block.value();
            }
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION > 344
        int id_;
#endif
        std::string command;
#if PROTOCOL_VERSION < 345
        bool assume_command;
        std::optional<NetworkPosition> looked_at_block;
#endif

    };
} //ProtocolCraft
