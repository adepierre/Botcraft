#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class TabCompleteServerbound : public BaseMessage<TabCompleteServerbound>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x01;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x05;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x06;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x06;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x06;
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x06;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Tab-Complete (serverbound)";
        }

#if PROTOCOL_VERSION > 344
        void SetTransactionId(const int transaction_id_)
        {
            transaction_id = transaction_id_;
        }
#endif

        void SetText(const std::string& text_)
        {
            text = text_;
        }

#if PROTOCOL_VERSION < 345
        void SetAssumeCommand(const bool assume_command_)
        {
            assume_command = assume_command_;
        }

        void SetHasPosition(const bool has_position_)
        {
            has_position = has_position_;
        }

        void SetLookedAtBlock(const NetworkPosition& looked_at_block_)
        {
            looked_at_block = looked_at_block_;
        }
#endif


#if PROTOCOL_VERSION > 344
        const int GetTransactionId() const
        {
            return transaction_id;
        }
#endif

        const std::string& GetText() const
        {
            return text;
        }

#if PROTOCOL_VERSION < 345
        const bool GetAssumeCommand() const
        {
            return assume_command;
        }

        const bool GetHasPosition() const
        {
            return has_position;
        }

        const NetworkPosition& GetLookedAtBlock() const
        {
            return looked_at_block;
        }
#endif



    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION > 344
            transaction_id = ReadVarInt(iter, length);
#endif
            text = ReadString(iter, length);
#if PROTOCOL_VERSION < 345
            assume_command = ReadData<bool>(iter, length);
            has_position = ReadData<bool>(iter, length); 
            if (has_position)
            {
                looked_at_block.Read(iter, length);
            }
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION > 344
            WriteVarInt(transaction_id, container);
#endif
            WriteString(text, container);
#if PROTOCOL_VERSION < 345
            WriteData<bool>(assume_command, container);
            WriteData<bool>(has_position, container);
            if (has_position)
            {
                looked_at_block.Write(container);
            }
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

#if PROTOCOL_VERSION > 344
            object["transaction_id"] = picojson::value((double)transaction_id);
#endif
            object["text"] = picojson::value(text);
#if PROTOCOL_VERSION < 345
            object["assume_command"] = picojson::value(assume_command);
            object["has_position"] = picojson::value(has_position);
            if (has_position)
            {
                object["looked_at_block"] = looked_at_block.Serialize();
            }
#endif

            return value;
        }

    private:
#if PROTOCOL_VERSION > 344
        int transaction_id;
#endif
        std::string text;
#if PROTOCOL_VERSION < 345
        bool assume_command;
        bool has_position;
        NetworkPosition looked_at_block;
#endif

    };
} //ProtocolCraft