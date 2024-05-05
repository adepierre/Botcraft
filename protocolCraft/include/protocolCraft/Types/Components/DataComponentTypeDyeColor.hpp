#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeDyeColor : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeDyeColor()
            {

            }


            int GetColorId() const
            {
                return color_id;
            }


            void SetColorId(const int color_id_)
            {
                color_id = color_id_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                color_id = ReadData<VarInt>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<VarInt>(color_id, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["color_id"] = color_id;

                return output;
            }

        private:
            int color_id;

        };
    }
}
#endif
