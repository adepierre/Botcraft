#pragma once

#include <memory>

#include "botcraft/NBT/Tag.hpp"

namespace Botcraft
{
    class TagDouble : public Tag
    {
    public:
        TagDouble();
        ~TagDouble();

        const double GetValue() const;
        void SetValue(const double v);

        virtual const TagType GetType() const override;

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        virtual const std::string Print(const std::string &prefix) const override;

    private:
        double value;
    };
}