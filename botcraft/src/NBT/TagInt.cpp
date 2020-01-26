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

    void TagInt::ReadImpl(ReadIterator &iterator, size_t &length)
    {
        value = ReadData<int>(iterator, length);
    }

    void TagInt::WriteImpl(WriteContainer &container) const
    {
        WriteData<int>(value, container);
    }

    const picojson::value TagInt::SerializeImpl() const
    {
        return picojson::value((double)value);
    }
}