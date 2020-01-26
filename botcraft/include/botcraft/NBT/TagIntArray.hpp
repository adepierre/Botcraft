#pragma once

#include <memory>

#include "botcraft/NBT/Tag.hpp"

namespace Botcraft
{
    class TagIntArray : public Tag
    {
    public:
        TagIntArray();
        ~TagIntArray();

        const std::vector<int>& GetValues() const;
        void SetValues(const std::vector<int> &v);

        virtual const TagType GetType() const override;

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        virtual const picojson::value SerializeImpl() const override;

    private:
        std::vector<int> values;
    };
}