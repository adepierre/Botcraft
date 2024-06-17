#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ServerLinksUnstrustedEntry : public NetworkType
    {
        DECLARE_FIELDS(
            (std::optional<VarInt>, std::optional<Chat>, std::string),
            (TypeId,                Uri,                 Link)
        );
        DECLARE_SERIALIZE;

        GETTER_SETTER(Link);


        const std::optional<int>& GetTypeId() const
        {
            return std::get<static_cast<size_t>(FieldsEnum::TypeId)>(fields);
        }

        auto& SetTypeId(const std::optional<int>& type_id)
        {
            std::get<static_cast<size_t>(FieldsEnum::TypeId)>(fields) = type_id;
            if (type_id.has_value())
            {
                std::get<static_cast<size_t>(FieldsEnum::Uri)>(fields) = {};
            }
            return *this;
        }


        const std::optional<Chat>& GetUri() const
        {
            return std::get<static_cast<size_t>(FieldsEnum::Uri)>(fields);
        }

        auto& SetUri(const std::optional<Chat>& uri)
        {
            std::get<static_cast<size_t>(FieldsEnum::Uri)>(fields) = uri;
            if (uri.has_value())
            {
                std::get<static_cast<size_t>(FieldsEnum::TypeId)>(fields) = {};
            }
            return *this;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            const bool is_type_id = ReadData<bool>(iter, length);
            if (is_type_id)
            {
                SetTypeId(ReadData<VarInt>(iter, length));
            }
            else
            {
                SetUri(ReadData<Chat>(iter, length));
            }
            SetLink(ReadData<std::string>(iter, length));
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            const bool is_type_id = GetTypeId().has_value();
            WriteData<bool>(is_type_id, container);
            if (is_type_id)
            {
                WriteData<VarInt>(GetTypeId().value(), container);
            }
            else
            {
                WriteData<Chat>(GetUri().value(), container);
            }
            WriteData<std::string>(GetLink(), container);
        }
    };
}
#endif
