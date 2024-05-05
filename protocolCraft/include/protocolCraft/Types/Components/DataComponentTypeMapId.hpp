#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeMapId : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeMapId()
            {

            }


            int GetId() const
            {
                return id;
            }


            void SetId(const int id_)
            {
                id = id_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                id = ReadData<VarInt>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<VarInt>(id, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["id"] = id;

                return output;
            }

        private:
            int id;

        };
    }
}
#endif
