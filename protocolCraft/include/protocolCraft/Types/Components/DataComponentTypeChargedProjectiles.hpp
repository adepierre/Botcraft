#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Slot.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeChargedProjectiles : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeChargedProjectiles()
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
                ReadVector<Slot>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteVector<Slot>(list, container);
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
