#pragma once

#if PROTOCOL_VERSION > 344
#include <memory>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"
#include "protocolCraft/Types/Identifier.hpp"


namespace ProtocolCraft 
{
    class CommandNode : public NetworkType
    {
    public:
        virtual ~CommandNode()
        {

        }

        void SetFlags(const char flags_)
        {
            flags = flags_;
        }

        void SetChildrenCount(const int children_count_)
        {
            children_count = children_count_;
        }

        void SetChildren(const std::vector<int>& children_)
        {
            children = children_;
        }

        void SetRedirectNode(const int redirect_node_)
        {
            redirect_node = redirect_node_;
        }

        void SetName(const std::string& name_)
        {
            name = name_;
        }

        void SetParser(const Identifier& parser_)
        {
            parser = parser_;
        }

        void SetProperties(const std::shared_ptr<BrigadierProperty> properties_)
        {
            properties = properties_;
        }

        void SetSuggestionsType(const Identifier& suggestions_type_)
        {
            suggestions_type = suggestions_type_;
        }


        const char GetFlags() const
        {
            return flags;
        }

        const int GetChildrenCount() const
        {
            return children_count;
        }

        const std::vector<int>& GetChildren() const
        {
            return children;
        }

        const int GetRedirectNode() const
        {
            return redirect_node;
        }

        const std::string& GetName() const
        {
            return name;
        }

        const Identifier& GetParser() const
        {
            return parser;
        }

        const std::shared_ptr<BrigadierProperty> GetProperties() const
        {
            return properties;
        }

        const Identifier& GetSuggestionsType() const
        {
            return suggestions_type;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            flags = ReadData<char>(iter, length);
            children_count = ReadData<VarInt>(iter, length);
            children = std::vector<int>(children_count);
            for (int i = 0; i < children_count; ++i)
            {
                children[i] = ReadData<VarInt>(iter, length);
            }
            if (flags & 0x08)
            {
                redirect_node = ReadData<VarInt>(iter, length);
            }
            const char node_type = flags & 0x03;
            if (node_type == 1 || node_type == 2)
            {
                name = ReadData<std::string>(iter, length);
            }
            if (node_type == 2)
            {
                parser.Read(iter, length);
                properties = BrigadierProperty::CreateProperties(parser);
                properties->Read(iter, length);
            }
            if (flags & 0x10)
            {
                suggestions_type.Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(flags, container);
            WriteData<VarInt>(children_count, container);
            for (int i = 0; i < children_count; ++i)
            {
                WriteData<VarInt>(children[i], container);
            }
            if (flags & 0x08)
            {
                WriteData<VarInt>(redirect_node, container);
            }
            const char node_type = flags & 0x03;
            if (node_type == 1 || node_type == 2)
            {
                WriteData<std::string>(name, container);
            }
            if (node_type == 2)
            {
                parser.Write(container);
                properties->Write(container);
            }
            if (flags & 0x10)
            {
                suggestions_type.Write(container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["flags"] = flags;
            output["children_count"] = children_count;
            output["children"] = children;

            if (flags & 0x08)
            {
                output["redirect_node"] = redirect_node;
            }

            const char node_type = flags & 0x03;
            if (node_type == 1 || node_type == 2)
            {
                output["name"] = name;
            }
            if (node_type == 2)
            {
                output["parser"] = parser.Serialize();
                output["properties"] = properties->Serialize();
            }
            if (flags & 0x10)
            {
                output["suggestions_type"] = suggestions_type.Serialize();
            }

            return output;
        }

    private:
        char flags;
        int children_count;
        std::vector<int> children;
        int redirect_node;
        std::string name;
        Identifier parser;
        std::shared_ptr<BrigadierProperty> properties;
        Identifier suggestions_type;

    };
} // ProtocolCraft
#endif
