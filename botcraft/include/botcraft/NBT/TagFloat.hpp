#pragma once

#include <memory>

#include "botcraft/NBT/Tag.hpp"

namespace Botcraft
{
    class TagFloat : public Tag
    {
    public:
        TagFloat();
        ~TagFloat();

        const float GetValue() const;
        void SetValue(const float v);

        virtual const TagType GetType() const override;

        virtual void Read(ReadIterator &iterator, size_t &length) override;
        virtual void Write(WriteContainer &container) const override;
        virtual const std::string Print(const std::string &prefix) const override;

    private:
        float value;
    };
}