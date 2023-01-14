#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NBT/Tag.hpp"

namespace ProtocolCraft
{
    namespace NBT
    {
        class Value : public Tag
        {
        public:
            Value();
            virtual ~Value() override;

            bool HasData() const;

            // TODO: add methods to deal with compressed files?
            friend std::istream& operator>>(std::istream& is, Value& v);

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
        };
    }
}
