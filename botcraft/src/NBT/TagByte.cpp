#pragma once

#include "botcraft/NBT/TagByte.hpp"

namespace Botcraft
{
    TagByte::TagByte()
    {

    }

    TagByte::~TagByte()
    {

    }

    const char TagByte::GetValue() const
    {
        return value;
    }

    void TagByte::SetValue(const char v)
    {
        value = v;
    }

    const TagType TagByte::GetType() const
    {
        return TagType::Byte;
    }

    void TagByte::Read(ReadIterator &iterator, size_t &length)
    {
        value = ReadData<char>(iterator, length);
    }

    void TagByte::Write(WriteContainer &container) const
    {
        WriteData<char>(value, container);
    }

    const std::string TagByte::Print(const std::string &prefix) const
    {
        return std::to_string(value);
    }
}