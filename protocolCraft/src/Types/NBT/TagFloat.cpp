#include "protocolCraft/Types/NBT/TagFloat.hpp"

namespace ProtocolCraft
{
    TagFloat::TagFloat()
    {

    }

    TagFloat::~TagFloat()
    {

    }
    
    float TagFloat::GetValue() const
    {
        return value;
    }

    void TagFloat::SetValue(const float v)
    {
        value = v;
    }

    TagType TagFloat::GetType() const
    {
        return TagType::Float;
    }

    void TagFloat::ReadImpl(ReadIterator &iterator, size_t &length)
    {
        value = ReadData<float>(iterator, length);
    }

    void TagFloat::WriteImpl(WriteContainer &container) const
    {
        WriteData<float>(value, container);
    }

    Json::Value TagFloat::SerializeImpl() const
    {
        return value;
    }
}