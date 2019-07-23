#include "botcraft/NBT/TagInt.hpp"

namespace Botcraft
{
    TagInt::TagInt()
    {

    }

    TagInt::~TagInt()
    {

    }

    const int TagInt::GetValue() const
    {
        return value;
    }

    void TagInt::SetValue(const int v)
    {
        value = v;
    }

    const TagType TagInt::GetType() const
    {
        return TagType::Int;
    }

    void TagInt::Read(ReadIterator &iterator, size_t &length)
    {
        value = ReadData<int>(iterator, length);
    }

    void TagInt::Write(WriteContainer &container) const
    {
        WriteData<int>(value, container);
    }

    const std::string TagInt::Print(const std::string &prefix) const
    {
        return std::to_string(value);
    }
}