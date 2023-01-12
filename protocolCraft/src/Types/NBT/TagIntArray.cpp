#include "protocolCraft/Types/NBT/TagIntArray.hpp"

namespace ProtocolCraft
{
    TagIntArray::TagIntArray()
    {

    }

    TagIntArray::~TagIntArray()
    {

    }

    const std::vector<int>& TagIntArray::GetValues() const
    {
        return values;
    }

    void TagIntArray::SetValues(const std::vector<int> &v)
    {
        values = v;
    }

    TagType TagIntArray::GetType() const
    {
        return TagType::IntArray;
    }

    void TagIntArray::ReadImpl(ReadIterator &iterator, size_t &length)
    {
        values = ReadVector<int, int>(iterator, length);
    }

    void TagIntArray::WriteImpl(WriteContainer &container) const
    {
        WriteVector<int, int>(values, container);
    }

    Json::Value TagIntArray::SerializeImpl() const
    {
        return values;
    }
}