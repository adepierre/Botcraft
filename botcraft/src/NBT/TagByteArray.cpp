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

    void TagByteArray::ReadImpl(ReadIterator &iterator, size_t &length)
    {
        const int data_size = ReadData<int>(iterator, length);
        values = ReadArrayData<char>(iterator, length, data_size);
    }

    void TagByteArray::WriteImpl(WriteContainer &container) const
    {
        WriteData<int>(values.size(), container);
        WriteArrayData<char>(values, container);
    }

    const picojson::value TagByteArray::SerializeImpl() const
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