#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeUnbreakable : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeUnbreakable()
            {

            }


            bool GetShowInTooltip() const
            {
                return show_in_tooltip;
            }


            void SetShowInTooltip(const bool show_in_tooltip_)
            {
                show_in_tooltip = show_in_tooltip_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                show_in_tooltip = ReadData<bool>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<bool>(show_in_tooltip, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["show_in_tooltip"] = show_in_tooltip;

                return output;
            }

        private:
            bool show_in_tooltip = true;

        };
    }
}
#endif
