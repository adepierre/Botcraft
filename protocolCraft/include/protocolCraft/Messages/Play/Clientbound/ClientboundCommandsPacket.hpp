#pragma once

#if PROTOCOL_VERSION > 344
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/CommandNode/CommandNode.hpp"

namespace ProtocolCraft
{
    class ClientboundCommandsPacket : public BaseMessage<ClientboundCommandsPacket>
    {
    public:
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 762 // 1.19.4
static constexpr int packet_id = 0x10;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Commands";

        virtual ~ClientboundCommandsPacket() override
        {

        }

        void SetNodes(const std::vector<CommandNode>& nodes_)
        {
            nodes = nodes_;
        }

        void SetRootIndex(const int root_index_)
        {
            root_index = root_index_;
        }


        const std::vector<CommandNode>& GetNodes() const
        {
            return nodes;
        }

        int GetRootIndex() const
        {
            return root_index;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            nodes = ReadVector<CommandNode>(iter, length);
            root_index = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVector<CommandNode>(nodes, container);
            WriteData<VarInt>(root_index, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["nodes"] = nodes;
            output["root_index"] = root_index;

            return output;
        }

    private:
        std::vector<CommandNode> nodes;
        int root_index;

    };
} //ProtocolCraft
#endif
