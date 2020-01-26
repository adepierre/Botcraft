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

    void TagIntArray::ReadImpl(ReadIterator &iterator, size_t &length)
    {
        const int data_size = ReadData<int>(iterator, length);
        values = ReadArrayData<int>(iterator, length, data_size);
    }

    void TagIntArray::WriteImpl(WriteContainer &container) const
    {
        WriteData<int>(values.size(), container);
        WriteArrayData<int>(values, container);
    }

    const picojson::value TagIntArray::SerializeImpl() const
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