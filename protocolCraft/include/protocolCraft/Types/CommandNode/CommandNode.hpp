#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#pragma once

#include <memory>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"
#include "protocolCraft/Types/Identifier.hpp"


namespace ProtocolCraft
{
    class CommandNode : public NetworkType
    {
        SERIALIZED_FIELD(Flags, char);
        SERIALIZED_FIELD(Children, std::vector<VarInt>);
        SERIALIZED_FIELD(RedirectNode, VarInt);
        SERIALIZED_FIELD(Name, std::string);
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        SERIALIZED_FIELD(Parser, Identifier);
#else
        SERIALIZED_FIELD(ParserId, Internal::DiffType<BrigadierPropertyType, VarInt>);
#endif
        SERIALIZED_FIELD(Properties, std::shared_ptr<BrigadierProperty>);
        SERIALIZED_FIELD(SuggestionType, Identifier);

        DEFINE_UTILITIES;

    public:
        virtual ~CommandNode()
        {

        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetFlags(ReadData<char>(iter, length));
            SetChildren(ReadData<std::vector<VarInt>>(iter, length));
            if (GetFlags() & 0x08)
            {
                SetRedirectNode(ReadData<VarInt>(iter, length));
            }
            const char node_type = GetFlags() & 0x03;
            if (node_type == 1 || node_type == 2)
            {
                SetName(ReadData<std::string>(iter, length));
            }
            if (node_type == 2)
            {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
                SetParser(ReadData<Identifier>(iter, length));
                SetProperties(BrigadierProperty::CreateProperties(GetParser()));
#else
                SetParserId(ReadData<BrigadierPropertyType, VarInt>(iter, length));
                SetProperties(BrigadierProperty::CreateProperties(GetParserId()));
#endif
                GetProperties()->Read(iter, length);
                if (GetFlags() & 0x10)
                {
                    SetSuggestionType(ReadData<Identifier>(iter, length));
                }
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(GetFlags(), container);
            WriteData<std::vector<VarInt>>(GetChildren(), container);
            if (GetFlags() & 0x08)
            {
                WriteData<VarInt>(GetRedirectNode(), container);
            }
            const char node_type = GetFlags() & 0x03;
            if (node_type == 1 || node_type == 2)
            {
                WriteData<std::string>(GetName(), container);
            }
            if (node_type == 2)
            {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
                WriteData<Identifier>(GetParser(), container);
#else
                WriteData<BrigadierPropertyType, VarInt>(GetParserId(), container);
#endif
                GetProperties()->Write(container);
                if (GetFlags() & 0x10)
                {
                    WriteData<Identifier>(GetSuggestionType(), container);
                }
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(field_name<Flags_index>)] = GetFlags();
            output[std::string(field_name<Children_index>)] = GetChildren();

            if (GetFlags() & 0x08)
            {
                output[std::string(field_name<RedirectNode_index>)] = GetRedirectNode();
            }

            const char node_type = GetFlags() & 0x03;
            if (node_type == 1 || node_type == 2)
            {
                output[std::string(field_name<Name_index>)] = GetName();
            }
            if (node_type == 2)
            {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
                output[std::string(field_name<Parser_index>)] = GetParser();
#else
                output[std::string(field_name<ParserId_index>)] = GetParserId();
#endif
                output[std::string(field_name<Properties_index>)] = GetProperties()->Serialize();
                if (GetFlags() & 0x10)
                {
                    output[std::string(field_name<SuggestionType_index>)] = GetSuggestionType();
                }
            }

            return output;
        }
    };
} // ProtocolCraft
#endif
