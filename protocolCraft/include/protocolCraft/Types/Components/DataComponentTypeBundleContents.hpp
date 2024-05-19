#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeBundleContents : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeBundleContents()
            {

            }


            const std::vector<Slot>& GetList() const
            {
                return list;
            }


            void SetList(const std::vector<Slot>& list_)
            {
                list = list_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                ReadData<std::vector<Slot>>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<std::vector<Slot>>(list, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["list"] = list;

                return output;
            }

        private:
            std::vector<Slot> list;

        };
    }
}
#endif
