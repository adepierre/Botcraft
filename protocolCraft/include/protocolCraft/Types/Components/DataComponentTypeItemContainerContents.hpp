#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeItemContainerContents : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeItemContainerContents()
            {

            }


            const std::vector<Slot>& GetItems() const
            {
                return items;
            }


            void SetItems(const std::vector<Slot>& items_)
            {
                items = items_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                items = ReadData<std::vector<Slot>>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<std::vector<Slot>>(items, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["items"] = items;

                return output;
            }

        private:
            std::vector<Slot> items;

        };
    }
}
#endif
