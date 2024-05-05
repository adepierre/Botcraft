#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeHolderInstrument : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeHolderInstrument()
            {

            }


            int GetInstrumentId() const
            {
                return instrument_id;
            }


            void SetInstrumentId(const int instrument_id_)
            {
                instrument_id = instrument_id_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                instrument_id = ReadData<VarInt>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<VarInt>(instrument_id, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["instrument_id"] = instrument_id;

                return output;
            }

        private:
            int instrument_id = 0;

        };
    }
}
#endif
