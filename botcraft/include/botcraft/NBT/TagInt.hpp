#pragma once

#include <memory>

#include "botcraft/NBT/Tag.hpp"

namespace Botcraft
{
    class TagInt : public Tag
    {
    public:
        TagInt();
        ~TagInt();

        const int GetValue() const;
        void SetValue(const int v);

        virtual const TagType GetType() const override;

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        virtual const std::string Print(const std::string &prefix) const override;

    private:
        int value;
    };
}