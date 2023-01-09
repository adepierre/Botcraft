#pragma once

#include <memory>

#include "protocolCraft/Types/NBT/Tag.hpp"

namespace ProtocolCraft
{
    class TagDouble : public Tag
    {
    public:
        TagDouble();
        virtual ~TagDouble();

        double GetValue() const;
        void SetValue(const double v);

        virtual TagType GetType() const override;

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        virtual Json::Value SerializeImpl() const override;

    private:
        double value;
    };
}
