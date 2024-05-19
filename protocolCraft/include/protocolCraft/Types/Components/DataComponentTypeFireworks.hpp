#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeFireworkExplosion.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeFireworks : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeFireworks()
            {

            }


            int GetFlightDuration() const
            {
                return flight_duration;
            }

            const std::vector<DataComponentTypeFireworkExplosion>& GetExplosions() const
            {
                return explosions;
            }


            void SetFlightDuration(const int flight_duration_)
            {
                flight_duration = flight_duration_;
            }

            void SetExplosions(const std::vector<DataComponentTypeFireworkExplosion>& explosions_)
            {
                explosions = explosions_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                flight_duration = ReadData<VarInt>(iter, length);
                explosions = ReadData<std::vector<DataComponentTypeFireworkExplosion>>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<VarInt>(flight_duration, container);
                WriteData<std::vector<DataComponentTypeFireworkExplosion>>(explosions, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["flight_duration"] = flight_duration;
                output["explosions"] = explosions;

                return output;
            }

        private:
            int flight_duration = 0;
            std::vector<DataComponentTypeFireworkExplosion> explosions;

        };
    }
}
#endif
