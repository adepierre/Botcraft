#include "protocolCraft/Types/NBT/TagShort.hpp"

namespace ProtocolCraft
{
    TagShort::TagShort()
    {

    }

    TagShort::~TagShort()
    {

    }

    short TagShort::GetValue() const
    {
        return value;
    }

    void TagShort::SetValue(const short v)
    {
        value = v;
    }

    TagType TagShort::GetType() const
    {
        return TagType::Short;
    }

    void TagShort::ReadImpl(ReadIterator &iterator, size_t &length)
    {
        value = ReadData<short>(iterator, length);
    }

    void TagShort::WriteImpl(WriteContainer &container) const
    {
        WriteData<short>(value, container);
    }

    Json::Value TagShort::SerializeImpl() const
    {
        return Json::Value(value);
    }
}