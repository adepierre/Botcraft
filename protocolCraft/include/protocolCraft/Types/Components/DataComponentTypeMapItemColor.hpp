#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeMapItemColor : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeMapItemColor()
            {

            }


            int GetRGB() const
            {
                return rgb;
            }


            void SetRGB(const int rgb_)
            {
                rgb = rgb_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                rgb = ReadData<int>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<int>(rgb, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["rgb"] = rgb;

                return output;
            }

        private:
            int rgb;

        };
    }
}
#endif
