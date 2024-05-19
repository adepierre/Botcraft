#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Filterable.hpp"

#include <string>
#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeWritableBookContent : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeWritableBookContent()
            {

            }


            const std::vector<Filterable<std::string>>& GetPages() const
            {
                return pages;
            }


            void SetPages(const std::vector<Filterable<std::string>>& pages_)
            {
                pages = pages_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                pages = ReadData<std::vector<Filterable<std::string>>>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<std::vector<Filterable<std::string>>>(pages, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["pages"] = pages;

                return output;
            }

        private:
            std::vector<Filterable<std::string>> pages;

        };
    }
}
#endif
