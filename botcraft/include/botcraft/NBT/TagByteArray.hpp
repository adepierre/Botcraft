#pragma once

#include <memory>

#include "botcraft/NBT/Tag.hpp"

namespace Botcraft
{
    class TagByteArray : public Tag
    {
    public:
        TagByteArray();
        ~TagByteArray();

        const std::vector<char>& GetValues() const;
        void SetValues(const std::vector<char> &v);

        virtual const TagType GetType() const override;

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        virtual const std::string Print(const std::string &prefix) const override;

    private:
        std::vector<char> values;
    };
}