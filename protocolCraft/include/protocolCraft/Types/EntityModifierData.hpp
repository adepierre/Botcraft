#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class EntityModifierData : public NetworkType
    {
    public:
        virtual ~EntityModifierData() override
        {

        }

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
            uuid = ReadData<UUID>(iter, length);
            amount = ReadData<double>(iter, length);
            operation = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<UUID>(uuid, container);
            WriteData<double>(amount, container);
            WriteData<char>(operation, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["uuid"] = uuid;
            output["amount"] = amount;
            output["operation"] = operation;

            return output;
        }

    private:
        UUID uuid;
        double amount;
        char operation;
    };
}