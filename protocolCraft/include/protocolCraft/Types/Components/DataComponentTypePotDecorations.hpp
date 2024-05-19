#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypePotDecorations : public DataComponentType
        {
        public:
            virtual ~DataComponentTypePotDecorations()
            {

            }


            const std::vector<int>& GetSides() const
            {
                return sides;
            }


            void SetSides(const std::vector<int>& sides_)
            {
                sides = sides_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                sides = ReadData<std::vector<VarInt>>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<std::vector<VarInt>>(sides, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["sides"] = sides;

                return output;
            }

        private:
            std::vector<int> sides;

        };
    }
}
#endif
