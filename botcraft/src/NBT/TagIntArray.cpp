#pragma once

#include "botcraft/NBT/TagIntArray.hpp"

namespace Botcraft
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

    void TagIntArray::Read(ReadIterator &iterator, size_t &length)
    {
        const int data_size = ReadData<int>(iterator, length);
        values = ReadArrayData<int>(iterator, length, data_size);
    }

    void TagIntArray::Write(WriteContainer &container) const
    {
        WriteData<int>(values.size(), container);
        WriteArrayData<int>(values, container);
    }

    const std::string TagIntArray::Print(const std::string &prefix) const
    {
        return "[" + std::to_string(values.size()) + " Ints]";
    }
}