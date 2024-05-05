#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeRarity : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeRarity()
            {

            }


            int GetRarityId() const
            {
                return rarity_id;
            }


            void SetRarityId(const int rarity_id_)
            {
                rarity_id = rarity_id_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                rarity_id = ReadData<VarInt>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<VarInt>(rarity_id, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["rarity_id"] = rarity_id;

                return output;
            }

        private:
            int rarity_id;

        };
    }
}
#endif
