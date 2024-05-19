#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/BlockPredicate.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeAdventureModePredicate : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeAdventureModePredicate()
            {

            }


            const std::vector<BlockPredicate>& GetPredicates() const
            {
                return predicates;
            }

            bool GetShowInTooltip() const
            {
                return show_in_tooltip;
            }


            void SetPredicates(const std::vector<BlockPredicate>& predicates_)
            {
                predicates = predicates_;
            }

            void SetShowInTooltip(const bool show_in_tooltip_)
            {
                show_in_tooltip = show_in_tooltip_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                predicates = ReadData<std::vector<BlockPredicate>>(iter, length);
                show_in_tooltip = ReadData<bool>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<std::vector<BlockPredicate>>(predicates, container);
                WriteData<bool>(show_in_tooltip, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["predicates"] = predicates;
                output["show_in_tooltip"] = show_in_tooltip;

                return output;
            }

        private:
            std::vector<BlockPredicate> predicates;
            bool show_in_tooltip = true;

        };
    }
}
#endif
