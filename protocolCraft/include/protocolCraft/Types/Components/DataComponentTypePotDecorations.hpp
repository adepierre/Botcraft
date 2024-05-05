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
                sides = ReadVector<int>(iter, length, [](ReadIterator& i, size_t& l)
                    {
                        return ReadData<VarInt>(i, l);
                    });
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteVector<int>(sides, container, [](const int& i, WriteContainer& c)
                    {
                        WriteData<VarInt>(i, c);
                    });
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
