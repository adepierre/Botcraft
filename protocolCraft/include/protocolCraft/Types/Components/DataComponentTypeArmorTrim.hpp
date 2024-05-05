#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeArmorTrim : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeArmorTrim()
            {

            }


            int GetMaterial() const
            {
                return material;
            }

            int GetPattern() const
            {
                return pattern;
            }

            bool GetShowInTooltip() const
            {
                return show_in_tooltip;
            }


            void SetMaterial(const int material_)
            {
                material = material_;
            }

            void SetPattern(const int pattern_)
            {
                pattern = pattern_;
            }

            void SetShowInTooltip(const bool show_in_tooltip_)
            {
                show_in_tooltip = show_in_tooltip_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                material = ReadData<VarInt>(iter, length);
                pattern = ReadData<VarInt>(iter, length);
                show_in_tooltip = ReadData<bool>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<VarInt>(material, container);
                WriteData<VarInt>(pattern, container);
                WriteData<bool>(show_in_tooltip, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["material"] = material;
                output["pattern"] = pattern;
                output["show_in_tooltip"] = show_in_tooltip;

                return output;
            }

        private:
            int material = 0;
            int pattern = 0;
            bool show_in_tooltip = true;

        };
    }
}
#endif
