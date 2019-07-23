#pragma once

#include <memory>

#include "botcraft/NBT/Tag.hpp"

namespace Botcraft
{
    class TagLongArray : public Tag
    {
    public:
        TagLongArray();
        ~TagLongArray();

        const std::vector<long long int>& GetValues() const;
        void SetValues(const std::vector<long long int> &v);

        virtual const TagType GetType() const override;

        virtual void Read(ReadIterator &iterator, size_t &length) override;
        virtual void Write(WriteContainer &container) const override;
        virtual const std::string Print(const std::string &prefix) const override;

    private:
        std::vector<long long int> values;
    };
}