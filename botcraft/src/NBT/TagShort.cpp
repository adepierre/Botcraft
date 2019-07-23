#include "botcraft/NBT/TagShort.hpp"

namespace Botcraft
{
    TagShort::TagShort()
    {

    }

    TagShort::~TagShort()
    {

    }

    const short TagShort::GetValue() const
    {
        return value;
    }

    void TagShort::SetValue(const short v)
    {
        value = v;
    }

    const TagType TagShort::GetType() const
    {
        return TagType::Short;
    }

    void TagShort::Read(ReadIterator &iterator, size_t &length)
    {
        value = ReadData<short>(iterator, length);
    }

    void TagShort::Write(WriteContainer &container) const
    {
        WriteData<short>(value, container);
    }

    const std::string TagShort::Print(const std::string &prefix) const
    {
        return std::to_string(value);
    }
}