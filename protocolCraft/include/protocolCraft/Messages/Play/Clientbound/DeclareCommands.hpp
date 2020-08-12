#pragma once

#if PROTOCOL_VERSION > 344
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/CommandNode/CommandNode.hpp"

namespace ProtocolCraft
{
    class DeclareCommands : public BaseMessage<DeclareCommands>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x11;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x11;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x12;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x11;
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x10;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Declare Commands";
        }

        void SetCount(const int count_)
        {
            count = count_;
        }

        void SetNodes(const std::vector<CommandNode>& nodes_)
        {
            nodes = nodes_;
        }

        void SetRootIndex(const int root_index_)
        {
            root_index = root_index_;
        }


        const int GetCount() const
        {
            return count;
        }

        const std::vector<CommandNode>& GetNodes() const
        {
            return nodes;
        }

        const int GetRootIndex() const
        {
            return root_index;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            count = ReadVarInt(iter, length);
            nodes = std::vector<CommandNode>(count);
            for (int i = 0; i < count; ++i)
            {
                nodes[i].Read(iter, length);
            }
            root_index = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(count, container);
            for (int i = 0; i < count; ++i)
            {
                nodes[i].Write(container);
            }
            WriteVarInt(root_index, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["count"] = picojson::value((double)count);
            object["nodes"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["nodes"].get<picojson::array>();
            for (int i = 0; i < count; ++i)
            {
                array.push_back(nodes[i].Serialize());
            }
            object["root_index"] = picojson::value((double)root_index);

            return value;
        }

    private:
        int count;
        std::vector<CommandNode> nodes;
        int root_index;

    };
} //ProtocolCraft
#endif
