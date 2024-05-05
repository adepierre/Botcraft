#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeDyedItemColor : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeDyedItemColor()
            {

            }


            int GetRgb() const
            {
                return rgb;
            }

            bool GetShowInTooltip() const
            {
                return show_in_tooltip;
            }


            void SetRgb(const int rgb_)
            {
                rgb = rgb_;
            }

            void SetShowInTooltip(const bool show_in_tooltip_)
            {
                show_in_tooltip = show_in_tooltip_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                rgb = ReadData<int>(iter, length);
                show_in_tooltip = ReadData<bool>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<int>(rgb, container);
                WriteData<bool>(show_in_tooltip, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["rgb"] = rgb;
                output["show_in_tooltip"] = show_in_tooltip;

                return output;
            }

        private:
            int rgb = 0;
            bool show_in_tooltip = true;

        };
    }
}
#endif
