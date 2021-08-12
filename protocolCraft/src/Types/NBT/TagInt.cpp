#include "protocolCraft/Types/NBT/TagInt.hpp"

namespace ProtocolCraft
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

    const nlohmann::json TagInt::SerializeImpl() const
    {
        return nlohmann::json(value);
    }
}