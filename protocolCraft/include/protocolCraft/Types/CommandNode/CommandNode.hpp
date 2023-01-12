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

#if PROTOCOL_VERSION < 759
        void SetParser(const Identifier& parser_)
        {
            parser = parser_;
        }
#else
        void SetParserId(const int parser_id_)
        {
            parser_id = parser_id_;
        }
#endif

        void SetProperties(const std::shared_ptr<BrigadierProperty> properties_)
        {
            properties = properties_;
        }

        void SetSuggestionsType(const Identifier& suggestions_type_)
        {
            suggestions_type = suggestions_type_;
        }


        char GetFlags() const
        {
            return flags;
        }

        const std::vector<int>& GetChildren() const
        {
            return children;
        }

        int GetRedirectNode() const
        {
            return redirect_node;
        }

        const std::string& GetName() const
        {
            return name;
        }

#if PROTOCOL_VERSION < 759
        const Identifier& GetParser() const
        {
            return parser;
        }
#else
        int GetParserId() const
        {
            return parser_id;
        }
#endif

        std::shared_ptr<BrigadierProperty> GetProperties() const
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
            children = ReadVector<int>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadData<VarInt>(i, l);
                }
            );
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
#if PROTOCOL_VERSION < 759
                parser = ReadData<Identifier>(iter, length);
                properties = BrigadierProperty::CreateProperties(parser);
#else
                parser_id = ReadData<VarInt>(iter, length);
                properties = BrigadierProperty::CreateProperties(parser_id);
#endif
                properties->Read(iter, length);
                if (flags & 0x10)
                {
                    suggestions_type = ReadData<Identifier>(iter, length);
                }
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(flags, container);
            WriteVector<int>(children, container,
                [](const int& i, WriteContainer& c)
                {
                    WriteData<VarInt>(i, c);
                }
            );
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
#if PROTOCOL_VERSION < 759
                WriteData<Identifier>(parser, container);
#else
                WriteData<VarInt>(parser_id, container);
#endif
                properties->Write(container);
                if (flags & 0x10)
                {
                    WriteData<Identifier>(suggestions_type, container);
                }
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["flags"] = flags;
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
#if PROTOCOL_VERSION < 759
                output["parser"] = parser;
#else
                output["parser_id"] = parser_id;
#endif
                output["properties"] = properties->Serialize();
                if (flags & 0x10)
                {
                    output["suggestions_type"] = suggestions_type;
                }
            }

            return output;
        }

    private:
        char flags;
        std::vector<int> children;
        int redirect_node;
        std::string name;
#if PROTOCOL_VERSION < 759
        Identifier parser;
#else
        int parser_id;
#endif
        std::shared_ptr<BrigadierProperty> properties;
        Identifier suggestions_type;

    };
} // ProtocolCraft
#endif
