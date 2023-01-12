#include "protocolCraft/Types/NBT/TagByte.hpp"

namespace ProtocolCraft
{
    TagByte::TagByte()
    {

    }

    TagByte::~TagByte()
    {

    }

    char TagByte::GetValue() const
    {
        return value;
    }

    void TagByte::SetValue(const char v)
    {
        value = v;
    }

    TagType TagByte::GetType() const
    {
        return TagType::Byte;
    }

    void TagByte::ReadImpl(ReadIterator &iterator, size_t &length)
    {
        value = ReadData<char>(iterator, length);
    }

    void TagByte::WriteImpl(WriteContainer &container) const
    {
        WriteData<char>(value, container);
    }

    Json::Value TagByte::SerializeImpl() const
    {
        return value;
    }
}