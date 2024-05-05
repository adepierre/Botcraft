#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeItemLore : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeItemLore()
            {

            }


            const std::vector<Chat>& GetLines() const
            {
                return lines;
            }


            void SetLines(const std::vector<Chat>& lines_)
            {
                lines = lines_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                lines = ReadVector<Chat>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteVector<Chat>(lines, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["lines"] = lines;

                return output;
            }

        private:
            std::vector<Chat> lines;

        };
    }
}
#endif
