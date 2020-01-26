#include "botcraft/NBT/TagString.hpp"

namespace Botcraft
{
    TagString::TagString()
    {

    }

    TagString::~TagString()
    {

    }

    const std::string& TagString::GetValue() const
    {
        return value;
    }

    void TagString::SetValue(const std::string &v)
    {
        value = v;
    }

    const TagType TagString::GetType() const
    {
        return TagType::String;
    }

    void TagString::ReadImpl(ReadIterator &iterator, size_t &length)
    {
        const unsigned short string_size = ReadData<unsigned short>(iterator, length);
        value = ReadRawString(iterator, length, string_size);
    }

    void TagString::WriteImpl(WriteContainer &container) const
    {
        WriteData<unsigned short>(value.size(), container);
        WriteRawString(value, container);
    }

    const picojson::value TagString::SerializeImpl() const
    {
        return picojson::value(value);
    }
}