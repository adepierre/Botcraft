#pragma once

#include <vector>
#include <array>
#include <string>
#include <cstring>
#include <algorithm>
#include <stdexcept>
#include <type_traits>
#include <optional>
#include <functional>
#include <map>
#if PROTOCOL_VERSION > 760
#include <bitset>
#endif

namespace ProtocolCraft
{
    class NetworkType;

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

    template<
        typename T,
        typename std::enable_if<!std::is_base_of<NetworkType, T>::value, bool>::type = true
    >
    T ReadData(ReadIterator &iter, size_t &length)
    {
        if (length < sizeof(T))
        {
            throw std::runtime_error("Not enough input in ReadData");
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

    template<
        typename T,
        typename std::enable_if<std::is_base_of<NetworkType, T>::value, bool>::type = true
    >
    T ReadData(ReadIterator& iter, size_t& length)
    {
        T output;
        output.Read(iter, length);
        return output;
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

    template<
        typename T,
        typename std::enable_if<!std::is_base_of<NetworkType, T>::value, bool>::type = true
    >
    void WriteData(const T& value, WriteContainer& container)
    {
        std::vector<unsigned char> output(sizeof(T));

        // Don't need to change endianess of char!
        if constexpr(sizeof(T) > 1)
        {
            // Little endian check
            // It doesn't work if int and char
            // have the same size, but I guess this is not
            // the only thing that souldn't work in this case
            constexpr int num = 1;
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

    template<
        typename T,
        typename std::enable_if<std::is_base_of<NetworkType, T>::value, bool>::type = true
    >
    void WriteData(const T& value, WriteContainer& container)
    {
        value.Write(container);
    }

    template<>
    void WriteData(const std::string& value, WriteContainer& container);

    template<>
    void WriteData(const VarInt& value, WriteContainer &container);

    template<>
    void WriteData(const VarLong& value, WriteContainer& container);

    // We could use base WriteData<T>, but sizeof(std::array<?, N>)
    // is not guaranteed to be N
    template<>
    void WriteData(const UUID& value, WriteContainer& container);


    template<typename T>
    std::optional<T> ReadOptional(ReadIterator& iter, size_t& length, const std::function<T(ReadIterator&, size_t&)>& read_func = ReadData<T>)
    {
        std::optional<T> output;

        const bool has_value = ReadData<bool>(iter, length);
        if (has_value)
        {
            output = read_func(iter, length);
        }

        return output;
    }

    template<typename T>
    void WriteOptional(const std::optional<T>& value, WriteContainer& container, const std::function<void(const T&, WriteContainer&)>& write_func = WriteData<T>)
    {
        WriteData<bool>(value.has_value(), container);
        if (value.has_value())
        {
            write_func(value.value(), container);
        }
    }


    template<typename T, typename SizeType = VarInt>
    std::vector<T> ReadVector(ReadIterator& iter, size_t& length)
    {
        const int output_length = ReadData<SizeType>(iter, length);

        std::vector<T> output(output_length);

        if constexpr(sizeof(T) == 1 && !std::is_base_of<NetworkType, T>::value)
        {
            if (length < output_length)
            {
                throw std::runtime_error("Not enough input in ReadVector");
            }

            memcpy(output.data(), &(*iter), output_length);
            length -= output_length;
            iter += output_length;
        }
        else
        {
            for (int i = 0; i < output_length; ++i)
            {
                output[i] = ReadData<T>(iter, length);
            }
        }

        return output;
    }

    template<typename T, typename SizeType = VarInt>
    std::vector<T> ReadVector(ReadIterator& iter, size_t& length, const std::function<T(ReadIterator&, size_t&)>& read_func)
    {
        const int output_length = ReadData<SizeType>(iter, length);

        std::vector<T> output(output_length);
        for (int i = 0; i < output_length; ++i)
        {
            output[i] = read_func(iter, length);
        }

        return output;
    }

    template<typename T, typename SizeType = VarInt>
    void WriteVector(const std::vector<T>& value, WriteContainer& container)
    {
        WriteData<SizeType>(static_cast<int>(value.size()), container);
        if constexpr (sizeof(T) == 1 && !std::is_base_of<NetworkType, T>::value)
        {
            container.insert(container.end(), value.begin(), value.end());
        }
        else
        {
            for (const auto& e: value)
            {
                WriteData<T>(e, container);
            }
        }
    }

    template<typename T, typename SizeType = VarInt>
    void WriteVector(const std::vector<T>& value, WriteContainer& container, const std::function<void(const T&, WriteContainer&)>& write_func)
    {
        WriteData<SizeType>(static_cast<int>(value.size()), container);
        for (const auto& e: value)
        {
            write_func(e, container);
        }
    }


    template<typename K, typename V, typename SizeType = VarInt>
    std::map<K, V> ReadMap(ReadIterator& iter, size_t& length)
    {
        const int output_length = ReadData<SizeType>(iter, length);

        std::map<K, V> output;
        for (int i = 0; i < output_length; ++i)
        {
            const K key = ReadData<K>(iter, length);
            const V val = ReadData<V>(iter, length);
            output.insert(std::make_pair(key, val));
        }

        return output;
    }

    template<typename K, typename V, typename SizeType = VarInt>
    std::map<K, V> ReadMap(ReadIterator& iter, size_t& length, const std::function<std::pair<const K, V>(ReadIterator&, size_t&)>& read_func)
    {
        const int output_length = ReadData<SizeType>(iter, length);

        std::map<K, V> output;
        for (int i = 0; i < output_length; ++i)
        {
            output.insert(read_func(iter, length));
        }

        return output;
    }

    template<typename K, typename V, typename SizeType = VarInt>
    void WriteMap(const std::map<K, V>& value, WriteContainer& container)
    {
        WriteData<SizeType>(static_cast<int>(value.size()), container);
        for (const auto& p : value)
        {
            WriteData<K>(p.first, container);
            WriteData<V>(p.second, container);
        }
    }

    template<typename K, typename V, typename SizeType = VarInt>
    void WriteMap(const std::map<K, V>& value, WriteContainer& container, const std::function<void(const std::pair<const K, V>&, WriteContainer&)>& write_func)
    {
        WriteData<SizeType>(static_cast<int>(value.size()), container);
        for (const auto& p : value)
        {
            write_func(p, container);
        }
    }


#if PROTOCOL_VERSION > 760
    template<size_t N>
    std::bitset<N> ReadBitset(ReadIterator& iter, size_t& length)
    {
        std::bitset<N> output;
        const std::vector<unsigned char> bytes = ReadByteArray(iter, length, N / 8 + (N % 8 != 0));
        for (size_t i = 0; i < N; ++i)
        {
            output.set(i, (bytes[i / 8] >> (i % 8)) & 0x01);
        }

        return output;
    }

    template<size_t N>
    void WriteBitset(const std::bitset<N>& values, WriteContainer& container)
    {
        std::vector<unsigned char> bytes(N / 8 + (N % 8 != 0), 0);
        for (size_t i = 0; i < N; ++i)
        {
            if (values[i])
            {
                bytes[i / 8] |= 1 << (i % 8);
            }
        }
        WriteByteArray(bytes, container);
    }

#endif
} // ProtocolCraft
