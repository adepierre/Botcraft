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
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS_TYPES(char,  std::vector<VarInt>, VarInt,       std::string, Identifier, std::shared_ptr<BrigadierProperty>, Identifier);
        DECLARE_FIELDS_NAMES(Flags, Children,            RedirectNode, Name,        Parser,     Properties,                         SuggestionType);
#else
        DECLARE_FIELDS_TYPES(char,  std::vector<VarInt>, VarInt,       std::string, DiffType<BrigadierPropertyType, VarInt>,   std::shared_ptr<BrigadierProperty>, Identifier);
        DECLARE_FIELDS_NAMES(Flags, Children,            RedirectNode, Name,        ParserId,                                  Properties,                         SuggestionType);
#endif

        GETTER_SETTER(Flags);
        GETTER_SETTER(Children);
        GETTER_SETTER(RedirectNode);
        GETTER_SETTER(Name);
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        GETTER_SETTER(Parser);
#else
        GETTER_SETTER(ParserId);
#endif
        GETTER_SETTER(Properties);
        GETTER_SETTER(SuggestionType);

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

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Flags)])] = GetFlags();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Children)])] = GetChildren();

            if (GetFlags() & 0x08)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::RedirectNode)])] = GetRedirectNode();
            }

            const char node_type = GetFlags() & 0x03;
            if (node_type == 1 || node_type == 2)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Name)])] = GetName();
            }
            if (node_type == 2)
            {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Parser)])] = GetParser();
#else
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::ParserId)])] = GetParserId();
#endif
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Properties)])] = GetProperties()->Serialize();
                if (GetFlags() & 0x10)
                {
                    output[std::string(json_names[static_cast<size_t>(FieldsEnum::SuggestionType)])] = GetSuggestionType();
                }
            }

            return output;
        }
    };
} // ProtocolCraft
#endif
