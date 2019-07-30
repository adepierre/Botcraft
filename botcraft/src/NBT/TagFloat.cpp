#include "botcraft/NBT/TagFloat.hpp"

namespace Botcraft
{
    TagFloat::TagFloat()
    {

    }

    TagFloat::~TagFloat()
    {

    }
    
    const float TagFloat::GetValue() const
    {
        return value;
    }

    void TagFloat::SetValue(const float v)
    {
        value = v;
    }

    const TagType TagFloat::GetType() const
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

    const std::string TagFloat::Print(const std::string &prefix) const
    {
        return std::to_string(value);
    }
}