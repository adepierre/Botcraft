#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ServerLinksUnstrustedEntry : public NetworkType
    {
    private: using THIS = ServerLinksUnstrustedEntry;

        DEFINE_CONDITION(HasTypeId, GetIsTypeId());
        DEFINE_CONDITION(HasUri, !GetIsTypeId());

        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(IsTypeId, bool);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(TypeId, Internal::Conditioned<VarInt, &THIS::HasTypeId>);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Uri, Internal::Conditioned<Chat, &THIS::HasUri>);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Link, std::string);

        DECLARE_READ_WRITE_SERIALIZE;

        GETTER(TypeId);
        GETTER(Uri);
        GETTER_SETTER(Link);

    protected:
        bool GetIsTypeId() const
        {
            return IsTypeId;
        }

    public:
        auto& SetTypeId(const std::optional<int>& TypeId_)
        {
            TypeId = TypeId_;
            IsTypeId = TypeId.has_value();
            if (TypeId.has_value())
            {
                Uri = std::nullopt;
            }
            return *this;
        }

        auto& SetUri(const std::optional<Chat>& Uri_)
        {
            Uri = Uri_;
            IsTypeId = !Uri.has_value();
            if (Uri.has_value())
            {
                TypeId = std::nullopt;
            }
            return *this;
        }
    };
}
#endif
