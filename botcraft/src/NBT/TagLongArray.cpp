#pragma once

#include "botcraft/NBT/TagLongArray.hpp"

namespace Botcraft
{
    TagLongArray::TagLongArray()
    {

    }

    TagLongArray::~TagLongArray()
    {

    }

    const std::vector<long long int>& TagLongArray::GetValues() const
    {
        return values;
    }

    void TagLongArray::SetValues(const std::vector<long long int> &v)
    {
        values = v;
    }

    const TagType TagLongArray::GetType() const
    {
        return TagType::LongArray;
    }

    void TagLongArray::Read(ReadIterator &iterator, size_t &length)
    {
        const int data_size = ReadData<int>(iterator, length);
        values = ReadArrayData<long long int>(iterator, length, data_size);
    }

    void TagLongArray::Write(WriteContainer &container) const
    {
        WriteData<int>(values.size(), container);
        WriteArrayData<long long int>(values, container);
    }

    const std::string TagLongArray::Print(const std::string &prefix) const
    {
        return "[" + std::to_string(values.size()) + " Longs]";
    }
}