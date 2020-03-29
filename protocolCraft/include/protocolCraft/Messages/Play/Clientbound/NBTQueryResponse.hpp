#pragma once

#if PROTOCOL_VERSION > 388
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{
    class NBTQueryResponse : public BaseMessage<NBTQueryResponse>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x1D;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x54;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x55;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "NBT Query Response";
        }

        void SetTransactionId(const int transaction_id_)
        {
            transaction_id = transaction_id_;
        }

        void SetNbt(const NBT& nbt_)
        {
            nbt = nbt_;
        }


        const int GetTransactionId() const
        {
            return transaction_id;
        }

        const NBT& GetNbt() const
        {
            return nbt;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            transaction_id = ReadVarInt(iter, length);
            nbt.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(transaction_id, container);
            nbt.Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["transaction_id"] = picojson::value((double)transaction_id);
            object["nbt"] = nbt.Serialize();

            return value;
        }

    private:
        int transaction_id;
        NBT nbt;

    };
} //ProtocolCraft
#endif
