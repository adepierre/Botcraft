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

#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        class UntrustedValue : public Tag
        {
        public:
            UntrustedValue();
            UntrustedValue(const Value& named);
            UntrustedValue(Value&& named);
            virtual ~UntrustedValue() override;

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
            virtual void WriteImpl(WriteContainer& container) const override;
        };
#endif

        class Value : public Tag
        {
        public:
            Value();
            Value(const UnnamedValue& unnamed);
            Value(UnnamedValue&& unnamed);
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
            Value(const UntrustedValue& untrusted);
            Value(UntrustedValue&& untrusted);
#endif

            virtual ~Value() override;

            bool HasData() const;

            friend std::istream& operator>>(std::istream& is, Value& v);
        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
        };
    }
}
