#include "protocolCraft/Types/NBT/TagLong.hpp"

namespace ProtocolCraft
{
    TagLong::TagLong()
    {

    }

    TagLong::~TagLong()
    {

    }

    const long long int TagLong::GetValue() const
    {
        return value;
    }

    void TagLong::SetValue(const long long int v)
    {
        value = v;
    }

    const TagType TagLong::GetType() const
    {
        return TagType::Long;
    }

    void TagLong::ReadImpl(ReadIterator &iterator, size_t &length)
    {
        value = ReadData<long long int>(iterator, length);
    }

    void TagLong::WriteImpl(WriteContainer &container) const
    {
        WriteData<long long int>(value, container);
    }

    const nlohmann::json TagLong::SerializeImpl() const
    {
        return nlohmann::json(value);
    }
}