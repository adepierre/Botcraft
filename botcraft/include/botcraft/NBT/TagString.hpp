#pragma once

#include <memory>

#include "botcraft/NBT/Tag.hpp"

namespace Botcraft
{
    class TagString : public Tag
    {
    public:
        TagString();
        ~TagString();

        const std::string& GetValue() const;
        void SetValue(const std::string &v);

        virtual const TagType GetType() const override;

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        virtual const std::string Print(const std::string &prefix) const override;

    private:
        std::string value;
    };
}