#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/ItemAttributeModifiersEntry.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeItemAttributeModifiers : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeItemAttributeModifiers()
            {

            }


            const std::vector<ItemAttributeModifiersEntry>& GetModifiers() const
            {
                return modifiers;
            }

            bool GetShowInTooltip() const
            {
                return show_in_tooltip;
            }


            void SetModifiers(const std::vector<ItemAttributeModifiersEntry>& modifiers_)
            {
                modifiers = modifiers_;
            }

            void SetShowInTooltip(const bool show_in_tooltip_)
            {
                show_in_tooltip = show_in_tooltip_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                modifiers = ReadVector<ItemAttributeModifiersEntry>(iter, length);
                show_in_tooltip = ReadData<bool>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteVector<ItemAttributeModifiersEntry>(modifiers, container);
                WriteData<bool>(show_in_tooltip, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["modifiers"] = modifiers;
                output["show_in_tooltip"] = show_in_tooltip;

                return output;
            }

        private:
            std::vector<ItemAttributeModifiersEntry> modifiers;
            bool show_in_tooltip = true;

        };
    }
}
#endif
