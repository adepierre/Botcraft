#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerSetContentPacket : public BaseMessage<ClientboundContainerSetContentPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Container Set Content";

#if PROTOCOL_VERSION < 756 /* < 1.17.1 */
        DECLARE_FIELDS(
            (unsigned char, std::vector<Slot>),
            (ContainerId,   Items)
        );
        DECLARE_SERIALIZE;
#else
        DECLARE_FIELDS(
            (unsigned char, VarInt,  std::vector<Slot>, Slot),
            (ContainerId,   StateId, Items,             CarriedItem)
        );
        DECLARE_READ_WRITE_SERIALIZE;
#endif

        GETTER_SETTER(ContainerId);
        GETTER_SETTER(Items);
#if PROTOCOL_VERSION > 755 /* > 1.17 */
        GETTER_SETTER(StateId);
        GETTER_SETTER(CarriedItem);
#endif

#if PROTOCOL_VERSION < 756 /* < 1.17.1 */
    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetContainerId(ReadData<unsigned char>(iter, length));
            // Special case, the data size is a short instead of a varint
            SetItems(ReadVector<Slot, short>(iter, length, ReadData<Slot>));
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<unsigned char>(GetContainerId(), container);
            WriteVector<Slot, short>(GetItems(), container, WriteData<Slot>);
        }
#endif
    };
} //ProtocolCraft
