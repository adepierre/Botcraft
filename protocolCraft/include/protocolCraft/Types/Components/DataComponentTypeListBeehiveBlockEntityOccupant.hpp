#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeCustomData.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeListBeehiveBlockEntityOccupant : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeListBeehiveBlockEntityOccupant()
            {

            }


            const DataComponentTypeCustomData& GetEntityData() const
            {
                return entity_data;
            }

            int GetTicksInHive() const
            {
                return ticks_in_hive;
            }

            int GetMinTicksInHive() const
            {
                return min_ticks_in_hive;
            }


            void SetEntityData(const DataComponentTypeCustomData& entity_data_)
            {
                entity_data = entity_data_;
            }

            void SetTicksInHive(const int ticks_in_hive_)
            {
                ticks_in_hive = ticks_in_hive_;
            }

            void SetMinTicksInHive(const int min_ticks_in_hive_)
            {
                min_ticks_in_hive = min_ticks_in_hive_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                entity_data = ReadData<DataComponentTypeCustomData>(iter, length);
                ticks_in_hive = ReadData<VarInt>(iter, length);
                min_ticks_in_hive = ReadData<VarInt>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<DataComponentTypeCustomData>(entity_data, container);
                WriteData<VarInt>(ticks_in_hive, container);
                WriteData<VarInt>(min_ticks_in_hive, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["entity_data"] = entity_data;
                output["ticks_in_hive"] = ticks_in_hive;
                output["min_ticks_in_hive"] = min_ticks_in_hive;

                return output;
            }

        private:
            DataComponentTypeCustomData entity_data;
            int ticks_in_hive = 0;
            int min_ticks_in_hive = 0;

        };
    }
}
#endif
