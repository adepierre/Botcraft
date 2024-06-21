#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEntityDataPacket : public BaseMessage<ClientboundSetEntityDataPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Entity Data";

        DECLARE_FIELDS(
            (VarInt, std::vector<unsigned char>),
            (Id_, PackedItems)
        );
        DECLARE_SERIALIZE;

        GETTER_SETTER(Id_);
        GETTER_SETTER(PackedItems);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetId_(ReadData<VarInt>(iter, length));
            SetPackedItems(ReadByteArray(iter, length, length));
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetId_(), container);
            WriteByteArray(GetPackedItems(), container);
        }
    };
} //ProtocolCraft
