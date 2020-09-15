#pragma once

#include <vector>
#include <string>
#include <algorithm>

namespace ProtocolCraft
{
    using ReadIterator = std::vector<unsigned char>::const_iterator;
    using WriteContainer = std::vector<unsigned char>;

    using Angle = unsigned char;
    using UUID = std::string;
    using Identifier = std::string;

    int ReadVarInt(ReadIterator &iter, size_t &length);
    void WriteVarInt(const int my_int, WriteContainer &container);

    long long int ReadVarLong(ReadIterator &iter, size_t &length);
    void WriteVarLong(const long long int my_long, WriteContainer &container);

    std::string ReadString(ReadIterator &iter, size_t &length);
    void WriteString(const std::string &my_string, WriteContainer &container);
    std::string ReadRawString(ReadIterator &iter, size_t &length, const int size);
    void WriteRawString(const std::string &s, WriteContainer &container);

    UUID ReadUUID(ReadIterator& iter, size_t& length);
    void WriteUUID(const UUID& s, WriteContainer& container);

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
    static T ReadData(ReadIterator &iter, size_t &length)
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

            // The compiler should(?) optimize that
            // This check doesn't work if int and char
            // have the same size, but I guess this is not
            // the only thing that souldn't work in this case
            const int num = 1;
            if (*(char *)&num == 1)
            {
                // Little endian
                return ChangeEndianness(output);
            }
            else
            {
                // Big endian
                return output;
            }
        }
    }

    template<typename T>
    static void WriteData(const T &value, WriteContainer &container)
    {
        std::vector<unsigned char> output(sizeof(T));

        T big_endian_var;
        // The compiler should(?) optimize that
        // This check doesn't work if int and char
        // have the same size, but I guess this is not
        // the only thing that souldn't work in this case
        const int num = 1;
        if (*(char *)&num == 1)
        {
            // Little endian
            big_endian_var = ChangeEndianness(value);
        }
        else
        {
            // Big endian
            big_endian_var = value;
        }

        memcpy(output.data(), &big_endian_var, sizeof(T));

        container.insert(container.end(), output.begin(), output.end());
    }

    template<typename T>
    static std::vector<T> ReadArrayData(ReadIterator &iter, size_t &length, const size_t size)
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

            // The compiler should(?) optimize that
            // This check doesn't work if int and char
            // have the same size, but I guess this is not
            // the only thing that souldn't work in this case
            const int num = 1;
            if (*(char *)&num == 1)
            {
                // Little endian
                for (int i = 0; i < size; ++i)
                {
                    output[i] = ChangeEndianness(output[i]);
                }
            }
            return output;
        }
    }

    template<typename T>
    static void WriteArrayData(const std::vector<T> &values, WriteContainer &container)
    {
        std::vector<unsigned char> bytes(sizeof(T));

        T big_endian_var;
        // The compiler should(?) optimize that
        // This check doesn't work if int and char
        // have the same size, but I guess this is not
        // the only thing that souldn't work in this case
        const int num = 1;

        for (int i = 0; i < values.size(); ++i)
        {
            if (*(char *)&num == 1)
            {
                // Little endian
                big_endian_var = ChangeEndianness(values[i]);
            }
            else
            {
                // Big endian
                big_endian_var = values[i];
            }
            memcpy(bytes.data(), &big_endian_var, sizeof(T));
            container.insert(container.end(), bytes.begin(), bytes.end());
        }
    }
} // Botcraft