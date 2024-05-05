#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeResourceLocation : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeResourceLocation()
            {

            }


            const Identifier& GetIdentifier() const
            {
                return identifier;
            }


            void SetIdentifier(const Identifier& identifier_)
            {
                identifier = identifier_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                identifier = ReadData<Identifier>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<Identifier>(identifier, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output = identifier;

                return output;
            }

        private:
            Identifier identifier;

        };
    }
}
#endif
