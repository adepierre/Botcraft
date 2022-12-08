#pragma once

#include <vector>
#include <array>
#include <string>
#include <cstring>
#include <algorithm>
#include <stdexcept>

namespace ProtocolCraft
{
    using ReadIterator = std::vector<unsigned char>::const_iterator;
    using WriteContainer = std::vector<unsigned char>;

    using Angle = unsigned char;
    using UUID = std::array<unsigned char, 16>;

    template <class T>
    class VarType
    {
    public:
        VarType(const T& val) : value(val) {}
        VarType() {}
        operator T() const { return value; }
    private:
        T value;
    };

    using VarInt = VarType<int>;
    using VarLong = VarType<long long int>;

    std::string ReadRawString(ReadIterator &iter, size_t &length, const int size);
    void WriteRawString(const std::string &s, WriteContainer &container);

    std::vector<unsigned char> ReadByteArray(ReadIterator &iter, size_t &length, const size_t &desired_length);
    void WriteByteArray(const std::vector<unsigned char> &my_array, WriteContainer &container);

    template <typename T>
    T ChangeEndianness(const T& in)
    {
        T in_cpy = in;
        std::vector<char> p(sizeof(T));
        memcpy(&p[0], &in_cpy, sizeof(T));
        std::reverse(p.begin(), p.end());
        memcpy(&in_cpy, &p[0], sizeof(T));
        return in_cpy;
    }

    template<typename T>
    T ReadData(ReadIterator &iter, size_t &length)
    {
        if (length < sizeof(T))
        {
            throw(std::runtime_error("Wrong input size in ReadData"));
        }
        else
        {
            T output;
            memcpy(&output, &(*iter), sizeof(T));
            length -= sizeof(T);
            iter += sizeof(T);

            // Don't need to change endianess of char!
            if (sizeof(T) > 1)
            {
                // The compiler should(?) optimize that
                // This check doesn't work if int and char
                // have the same size, but I guess this is not
                // the only thing that souldn't work in this case
                const int num = 1;
                if (*(char*)&num == 1)
                {
                    // Little endian
                    return ChangeEndianness(output);
                }
            }

            // Big endian or sizeof(1)
            return output;
        }
    }

    template<>
    std::string ReadData(ReadIterator& iter, size_t& length);

    template<>
    VarInt ReadData(ReadIterator& iter, size_t& length);

    template<>
    VarLong ReadData(ReadIterator& iter, size_t& length);

    // We could use base ReadData<T>, but sizeof(std::array<?, N>)
    // is not guaranteed to be N
    template<>
    UUID ReadData(ReadIterator& iter, size_t& length);

    template<typename T>
    void WriteData(const T& value, WriteContainer& container)
    {
        std::vector<unsigned char> output(sizeof(T));

        // Don't need to change endianess of char!
        if (sizeof(T) > 1)
        {
            // The compiler should(?) optimize that
            // This check doesn't work if int and char
            // have the same size, but I guess this is not
            // the only thing that souldn't work in this case
            const int num = 1;
            if (*(char*)&num == 1)
            {
                // Little endian
                T big_endian_var = ChangeEndianness(value);
                memcpy(output.data(), &big_endian_var, sizeof(T));
                container.insert(container.end(), output.begin(), output.end());
                return;
            }
        }

        // Big endian or sizeof(T) == 1
        memcpy(output.data(), &value, sizeof(T));
        container.insert(container.end(), output.begin(), output.end());
    }

    template<>
    void WriteData(const std::string &value, WriteContainer& container);

    template<>
    void WriteData(const VarInt &value, WriteContainer &container);

    template<>
    void WriteData(const VarLong& value, WriteContainer& container);

    // We could use base WriteData<T>, but sizeof(std::array<?, N>)
    // is not guaranteed to be N
    template<>
    void WriteData(const UUID& value, WriteContainer& container);


    template<typename T>
    std::vector<T> ReadArrayData(ReadIterator &iter, size_t &length, const size_t size)
    {
        if (length < size * sizeof(T))
        {
            throw(std::runtime_error("Wrong input size in ReadArrayData"));
        }
        else
        {
            std::vector<T> output(size);
            memcpy(output.data(), &(*iter), size * sizeof(T));
            length -= size * sizeof(T);
            iter += size * sizeof(T);

            if (sizeof(T) > 1)
            {
                // The compiler should(?) optimize that
                // This check doesn't work if int and char
                // have the same size, but I guess this is not
                // the only thing that souldn't work in this case
                const int num = 1;
                if (*(char*)&num == 1)
                {
                    // Little endian
                    for (int i = 0; i < size; ++i)
                    {
                        output[i] = ChangeEndianness(output[i]);
                    }
                }
            }
            return output;
        }
    }

    template<typename T>
    void WriteArrayData(const std::vector<T> &values, WriteContainer &container)
    {
        std::vector<unsigned char> bytes(sizeof(T));

        // The compiler should(?) optimize that
        // This check doesn't work if int and char
        // have the same size, but I guess this is not
        // the only thing that souldn't work in this case
        const int num = 1;

        for (int i = 0; i < values.size(); ++i)
        {
            if (sizeof(T) > 1)
            {
                if (*(char*)&num == 1)
                {
                    // Little endian
                    T big_endian_var = ChangeEndianness(values[i]);
                    memcpy(bytes.data(), &big_endian_var, sizeof(T));
                    container.insert(container.end(), bytes.begin(), bytes.end());
                    continue;
                }
            }

            // Big endian or sizeof(T) == 1
            memcpy(bytes.data(), &values[i], sizeof(T));
            container.insert(container.end(), bytes.begin(), bytes.end());
        }
    }
} // ProtocolCraft
