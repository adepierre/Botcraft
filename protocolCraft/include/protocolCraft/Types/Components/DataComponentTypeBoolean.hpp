#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeBoolean : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeBoolean()
            {

            }


            bool GetValue() const
            {
                return value;
            }


            void SetValue(const bool value_)
            {
                value = value_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                value = ReadData<bool>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<bool>(value, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["value"] = value;

                return output;
            }

        private:
            bool value = false;

        };
    }
}
#endif
