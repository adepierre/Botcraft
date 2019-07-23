#pragma once

#include <memory>

#include "botcraft/NBT/Tag.hpp"

namespace Botcraft
{
    class TagList : public Tag
    {
    public:
        TagList();
        ~TagList();

        const std::vector<std::shared_ptr<Tag> >& GetValues() const;
        void SetValues(const std::vector<std::shared_ptr<Tag> > &v);

        const TagType GetTagsType() const;
        void SetTagsType(const TagType tags_type_);

        virtual const TagType GetType() const override;

        virtual void Read(ReadIterator &iterator, size_t &length) override;
        virtual void Write(WriteContainer &container) const override;
        virtual const std::string Print(const std::string &prefix) const override;

    private:
        std::vector<std::shared_ptr<Tag> > tags;
        TagType tags_type;
    };
}