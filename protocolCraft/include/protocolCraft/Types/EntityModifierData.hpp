#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class EntityModifierData : public NetworkType
    {
    public:        
        void SetUuid(const UUID& uuid_)
        {
            uuid = uuid_;
        }

        void SetAmount(const double amount_)
        {
            amount = amount_;
        }

        void SetOperation(const char operation_)
        {
            operation = operation_;
        }


        const UUID& GetUuid() const
        {
            return uuid;
        }

        const double GetAmount() const
        {
            return amount;
        }
        
        const char GetOperation() const
        {
            return operation;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            uuid = ReadUUID(iter, length);
            amount = ReadData<double>(iter, length);
            operation = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteUUID(uuid, container);
            WriteData<double>(amount, container);
            WriteData<char>(operation, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["uuid"] = picojson::value(uuid);
            object["amount"] = picojson::value((double)amount);
            object["operation"] = picojson::value((double)operation);

            return value;
        }

    private:
        UUID uuid;
        double amount;
        char operation;
    };
}