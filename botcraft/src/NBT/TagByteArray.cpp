#pragma once

#include "botcraft/NBT/TagByteArray.hpp"

namespace Botcraft
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

    const TagType TagByteArray::GetType() const
    {
        return TagType::ByteArray;
    }

    void TagByteArray::Read(ReadIterator &iterator, size_t &length)
    {
        const int data_size = ReadData<int>(iterator, length);
        values = ReadArrayData<char>(iterator, length, data_size);
    }

    void TagByteArray::Write(WriteContainer &container) const
    {
        WriteData<int>(values.size(), container);
        WriteArrayData<char>(values, container);
    }

    const std::string TagByteArray::Print(const std::string &prefix) const
    {
        return "[" + std::to_string(values.size()) + " Bytes]";
    }
}