#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ServerLinksUnstrustedEntry : public NetworkType
    {
    private: using THIS = ServerLinksUnstrustedEntry;

        DECLARE_CONDITION(HasTypeId, GetIsTypeId());
        DECLARE_CONDITION(HasUri, !GetIsTypeId());

        DECLARE_FIELDS(
            (bool,     Internal::Conditioned<VarInt, &THIS::HasTypeId>, Internal::Conditioned<Chat, &THIS::HasUri>, std::string),
            (IsTypeId, TypeId,                                          Uri,                                        Link)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER       (TypeId);
        GETTER       (Uri);
        GETTER_SETTER(Link);

    protected:
        bool GetIsTypeId() const
        {
            return std::get<static_cast<size_t>(FieldsEnum::IsTypeId)>(fields);
        }

    public:
        auto& SetTypeId(const std::optional<int>& type_id)
        {
            std::get<static_cast<size_t>(FieldsEnum::TypeId)>(fields) = type_id;
            std::get<static_cast<size_t>(FieldsEnum::IsTypeId)>(fields) = type_id.has_value();
            if (type_id.has_value())
            {
                std::get<static_cast<size_t>(FieldsEnum::Uri)>(fields) = std::nullopt;
            }
            return *this;
        }

        auto& SetUri(const std::optional<Chat>& uri)
        {
            std::get<static_cast<size_t>(FieldsEnum::Uri)>(fields) = uri;
            std::get<static_cast<size_t>(FieldsEnum::IsTypeId)>(fields) = !uri.has_value();
            if (uri.has_value())
            {
                std::get<static_cast<size_t>(FieldsEnum::TypeId)>(fields) = std::nullopt;
            }
            return *this;
        }
    };
}
#endif
