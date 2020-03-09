#include "protocolCraft/Types/NBT/TagDouble.hpp"

namespace ProtocolCraft
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

    void TagDouble::ReadImpl(ReadIterator &iterator, size_t &length)
    {
        value = ReadData<double>(iterator, length);
    }

    void TagDouble::WriteImpl(WriteContainer &container) const
    {
        WriteData<double>(value, container);
    }

    const picojson::value TagDouble::SerializeImpl() const
    {
        return picojson::value(value);
    }
}