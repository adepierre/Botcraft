#pragma once

#include <vector>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/EntityProperty.hpp"

namespace ProtocolCraft
{
    class ClientboundUpdateAttributesPacket : public BaseMessage<ClientboundUpdateAttributesPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Update Attributes";

        DECLARE_FIELDS(
            (VarInt,   std::vector<EntityProperty>),
            (EntityId, Attributes)
        );
        DECLARE_SERIALIZE;

        GETTER_SETTER(EntityId);
        GETTER_SETTER(Attributes);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetEntityId(ReadData<VarInt>(iter, length));

#if PROTOCOL_VERSION < 755 /* < 1.17 */
            // Special case, size is a int instead of a varint
            SetAttributes(ReadVector<EntityProperty, int>(iter, length, ReadData<EntityProperty>));
#else
            SetAttributes(ReadData<std::vector<EntityProperty>>(iter, length));
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetEntityId(), container);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            // Special case, size is a int instead of a varint
            WriteVector<EntityProperty, int>(GetAttributes(), container, WriteData<EntityProperty>);
#else
            WriteData<std::vector<EntityProperty>>(GetAttributes(), container);
#endif
        }
    };
} //ProtocolCraft
