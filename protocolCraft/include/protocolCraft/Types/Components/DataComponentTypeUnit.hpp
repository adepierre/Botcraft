#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeUnit : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeUnit()
            {

            }


        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {

            }

            virtual void WriteImpl(WriteContainer& container) const override
            {

            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                return output;
            }

        };
    }
}
#endif
