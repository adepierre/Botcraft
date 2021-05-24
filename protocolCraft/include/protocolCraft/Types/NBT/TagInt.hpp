#pragma once

#include <memory>

#include "protocolCraft/Types/NBT/Tag.hpp"

namespace ProtocolCraft
{
    class TagInt : public Tag
    {
    public:
        TagInt();
        virtual ~TagInt();

        const int GetValue() const;
        void SetValue(const int v);

        virtual const TagType GetType() const override;

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        virtual const picojson::value SerializeImpl() const override;

    private:
        int value;
    };
}