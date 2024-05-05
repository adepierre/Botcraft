#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeCustomModelData : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeCustomModelData()
            {

            }


            int GetValue() const
            {
                return value;
            }


            void SetValue(const int value_)
            {
                value = value_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                value = ReadData<VarInt>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<VarInt>(value, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["value"] = value;

                return output;
            }

        private:
            int value;

        };
    }
}
#endif
