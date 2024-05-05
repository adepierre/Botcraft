#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class AttributeModifier : public NetworkType
        {
        public:
            virtual ~AttributeModifier()
            {

            }


            const UUID& GetId() const
            {
                return id;
            }

            const std::string& GetName() const
            {
                return name;
            }

            double GetAmount() const
            {
                return amount;
            }

            int GetOperation() const
            {
                return operation;
            }


            void SetId(const UUID& id_)
            {
                id = id_;
            }

            void SetName(const std::string& name_)
            {
                name = name_;
            }

            void SetAmount(const double amount_)
            {
                amount = amount_;
            }

            void SetOperation(const int operation_)
            {
                operation = operation_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                id = ReadData<UUID>(iter, length);
                name = ReadData<std::string>(iter, length);
                amount = ReadData<double>(iter, length);
                operation = ReadData<VarInt>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<UUID>(id, container);
                WriteData<std::string>(name, container);
                WriteData<double>(amount, container);
                WriteData<VarInt>(operation, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["id"] = id;
                output["name"] = name;
                output["amount"] = amount;
                output["operation"] = operation;

                return output;
            }

        private:
            UUID id = {};
            std::string name;
            double amount = 0.0;
            int operation = 0;

        };
    }
}
#endif
