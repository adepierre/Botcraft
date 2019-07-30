#pragma once

#include <memory>

#include "botcraft/NBT/Tag.hpp"

namespace Botcraft
{
    class TagLong : public Tag
    {
    public:
        TagLong();
        ~TagLong();

        const long long int GetValue() const;
        void SetValue(const long long int v);

        virtual const TagType GetType() const override;

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        virtual const std::string Print(const std::string &prefix) const override;

    private:
        long long int value;
    };
}