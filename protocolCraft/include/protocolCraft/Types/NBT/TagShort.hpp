#pragma once

#include <memory>

#include "protocolCraft/Types/NBT/Tag.hpp"

namespace ProtocolCraft
{
    class TagShort : public Tag
    {
    public:
        TagShort();
        virtual ~TagShort();

        short GetValue() const;
        void SetValue(const short v);

        virtual TagType GetType() const override;

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        virtual Json::Value SerializeImpl() const override;

    private:
        short value;
    };
}
