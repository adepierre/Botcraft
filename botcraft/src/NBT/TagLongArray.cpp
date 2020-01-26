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

    void TagLongArray::ReadImpl(ReadIterator &iterator, size_t &length)
    {
        const int data_size = ReadData<int>(iterator, length);
        values = ReadArrayData<long long int>(iterator, length, data_size);
    }

    void TagLongArray::WriteImpl(WriteContainer &container) const
    {
        WriteData<int>(values.size(), container);
        WriteArrayData<long long int>(values, container);
    }

    const picojson::value TagLongArray::SerializeImpl() const
    {
        picojson::value value(picojson::array_type, false);
        picojson::array& array = value.get<picojson::array>();

        for (int i = 0; i < values.size(); ++i)
        {
            array.push_back(picojson::value((double)values[i]));
        }

        return value;
    }
}