#pragma once

#include <memory>

#include "protocolCraft/Types/NBT/Tag.hpp"

namespace ProtocolCraft
{
    class TagList : public Tag
    {
    public:
        TagList();
        virtual ~TagList();

        const std::vector<std::shared_ptr<Tag> >& GetValues() const;
        void SetValues(const std::vector<std::shared_ptr<Tag> > &v);

        TagType GetTagsType() const;
        void SetTagsType(const TagType tags_type_);

        virtual TagType GetType() const override;

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        virtual const nlohmann::json SerializeImpl() const override;

    private:
        std::vector<std::shared_ptr<Tag> > tags;
        TagType tags_type;
    };
}
