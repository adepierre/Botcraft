#pragma once

#include <memory>

#include "protocolCraft/Types/NBT/Tag.hpp"

namespace ProtocolCraft
{
    class TagEnd : public Tag
    {
    public:
        TagEnd();
        virtual ~TagEnd();

        virtual TagType GetType() const override;

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        virtual Json::Value SerializeImpl() const override;
    };
}
