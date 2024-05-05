#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeDefault : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeDefault()
            {

            }


            const NBT::Value& GetTag() const
            {
                return tag;
            }


            void SetTag(const NBT::Value& tag_)
            {
                tag = tag_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                tag = ReadData<NBT::UnnamedValue>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<NBT::UnnamedValue>(tag, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["tag"] = tag;

                return output;
            }

        private:
            NBT::Value tag;

        };
    }
}
#endif
