#include "botcraft/NBT/TagEnd.hpp"

namespace Botcraft
{
    TagEnd::TagEnd()
    {

    }

    TagEnd::~TagEnd()
    {

    }

    const TagType TagEnd::GetType() const
    {
        return TagType::End;
    }

    void TagEnd::Read(ReadIterator &iterator, size_t &length)
    {

    }

    void TagEnd::Write(WriteContainer &container) const
    {

    }

    const std::string TagEnd::Print(const std::string &prefix) const
    {
        return "";
    }
}