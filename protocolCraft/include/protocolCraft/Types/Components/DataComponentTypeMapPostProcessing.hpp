#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeMapPostProcessing : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeMapPostProcessing()
            {

            }


            int GetMapPostProcessingId() const
            {
                return map_post_processing_id;
            }


            void SetMapPostProcessingId(const int map_post_processing_id_)
            {
                map_post_processing_id = map_post_processing_id_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                map_post_processing_id = ReadData<VarInt>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<VarInt>(map_post_processing_id, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["map_post_processing_id"] = map_post_processing_id;

                return output;
            }

        private:
            int map_post_processing_id;

        };
    }
}
#endif
