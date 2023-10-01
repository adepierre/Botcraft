#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NBT/Tag.hpp"

namespace ProtocolCraft
{
    namespace NBT
    {
        class Value;

        class UnnamedValue : public Tag
        {
        public:
            UnnamedValue();
            UnnamedValue(const Value& named);
            UnnamedValue(Value&& named);
            virtual ~UnnamedValue() override;

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
            virtual void WriteImpl(WriteContainer& container) const override;
        };

        class Value : public Tag
        {
        public:
            Value();
            Value(const UnnamedValue& unnamed);
            Value(UnnamedValue&& unnamed);

            virtual ~Value() override;

            bool HasData() const;

            friend std::istream& operator>>(std::istream& is, Value& v);
        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
        };
    }
}
