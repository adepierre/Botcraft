#pragma once

#include "botcraft/Network/BinaryReadWrite.hpp"
#include "botcraft/NBT/TagCompound.hpp"

namespace Botcraft
{
    class NBT
    {
    public:
        NBT();
        ~NBT();

        const TagCompound& GetRoot() const;
        const std::shared_ptr<Tag> GetTag(const std::string &s) const;
        const bool HasData() const;

        // TODO: add methods to deal with files // compression?

        void Read(ReadIterator &iterator, size_t &length);
        void Write(WriteContainer &container) const;
        const std::string Print() const;


    private:
        TagCompound root_tag;
        std::string root_name;
        bool has_data;
    };
}