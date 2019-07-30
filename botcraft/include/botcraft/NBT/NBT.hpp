#pragma once

#include "botcraft/Protocol/NetworkType.hpp"
#include "botcraft/NBT/TagCompound.hpp"

namespace Botcraft
{
    class NBT : public NetworkType
    {
    public:
        NBT();
        ~NBT();

        const TagCompound& GetRoot() const;
        const std::shared_ptr<Tag> GetTag(const std::string &s) const;
        const bool HasData() const;

        // TODO: add methods to deal with files // compression?

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        const std::string Print() const;


    private:
        TagCompound root_tag;
        std::string root_name;
        bool has_data;
    };
}