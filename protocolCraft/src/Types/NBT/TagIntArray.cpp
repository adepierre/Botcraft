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

    const TagType TagIntArray::GetType() const
    {
        return TagType::IntArray;
    }

    void TagIntArray::ReadImpl(ReadIterator &iterator, size_t &length)
    {
        const int data_size = ReadData<int>(iterator, length);
        values = ReadArrayData<int>(iterator, length, data_size);
    }

    void TagIntArray::WriteImpl(WriteContainer &container) const
    {
        WriteData<int>(static_cast<int>(values.size()), container);
        WriteArrayData<int>(values, container);
    }

    const nlohmann::json TagIntArray::SerializeImpl() const
    {
        return nlohmann::json(values);
    }
}