#include "protocolCraft/Types/NBT/TagByteArray.hpp"

namespace ProtocolCraft
{
    TagByteArray::TagByteArray()
    {

    }

    TagByteArray::~TagByteArray()
    {

    }

    const std::vector<char>& TagByteArray::GetValues() const
    {
        return values;
    }

    void TagByteArray::SetValues(const std::vector<char> &v)
    {
        values = v;
    }

    TagType TagByteArray::GetType() const
    {
        return TagType::ByteArray;
    }

    void TagByteArray::ReadImpl(ReadIterator &iterator, size_t &length)
    {
        ReadVector<char, int>(iterator, length);
    }

    void TagByteArray::WriteImpl(WriteContainer &container) const
    {
        WriteVector<char, int>(values, container);
    }

    Json::Value TagByteArray::SerializeImpl() const
    {
        return Json::Value(values);
    }
}