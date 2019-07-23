#include "botcraft/NBT/TagDouble.hpp"

namespace Botcraft
{
    TagDouble::TagDouble()
    {

    }

    TagDouble::~TagDouble()
    {

    }

    const double TagDouble::GetValue() const
    {
        return value;
    }

    void TagDouble::SetValue(const double v)
    {
        value = v;
    }

    const TagType TagDouble::GetType() const
    {
        return TagType::Double;
    }

    void TagDouble::Read(ReadIterator &iterator, size_t &length)
    {
        value = ReadData<double>(iterator, length);
    }

    void TagDouble::Write(WriteContainer &container) const
    {
        WriteData<double>(value, container);
    }

    const std::string TagDouble::Print(const std::string &prefix) const
    {
        return std::to_string(value);
    }
}