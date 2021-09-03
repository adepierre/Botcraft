#pragma once

#include <memory>

#include "protocolCraft/Types/NBT/Tag.hpp"

namespace ProtocolCraft
{
    class TagLong : public Tag
    {
    public:
        TagLong();
        virtual ~TagLong();

        const long long int GetValue() const;
        void SetValue(const long long int v);

        virtual const TagType GetType() const override;

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        virtual const nlohmann::json SerializeImpl() const override;

    private:
        long long int value;
    };
}