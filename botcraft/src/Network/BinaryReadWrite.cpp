#include "botcraft/Network/BinaryReadWrite.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
{
    int ReadVarInt(ReadIterator &iter, size_t &length)
    {
        int numRead = 0;
        int result = 0;

        unsigned char read;

        do
        {
            if (numRead >= length)
            {
                throw(std::runtime_error("Not enough input in ReadVarInt"));
            }

            read = *(iter + numRead);

            int value = (read & 127);//0b01111111
            result |= (value << (7 * numRead));

            numRead++;

            if (numRead > 5)
            {
                throw(std::runtime_error("VarInt is too big in ReadVarInt"));
            }

        } while ((read & 128) != 0);//0b10000000

        iter += numRead;
        length -= numRead;

        return result;
    }

    void WriteVarInt(const int my_int, WriteContainer &container)
    {
        unsigned int value = my_int;
        do {
            unsigned char temp = (unsigned char)(value & 127);//0b01111111
            value >>= 7;
            if (value != 0)
            {
                temp |= 128;//0b10000000
            }
            container.push_back(temp);
        } while (value != 0);
    }

    long long int ReadVarLong(ReadIterator &iter, size_t &length)
    {
        int numRead = 0;
        long long int result = 0;

        unsigned char read;

        do
        {
            if (numRead >= length)
            {
                throw(std::runtime_error("Not enough input in ReadVarLong"));
            }

            read = *(iter + numRead);

            long long int value = (read & 127);//0b01111111
            result |= (value << (7 * numRead));

            numRead++;

            if (numRead > 10)
            {
                throw(std::runtime_error("VarLong is too big in ReadVarLong"));
            }

        } while ((read & 128) != 0);//0b10000000

        iter += numRead;
        length -= numRead;

        return result;
    }

    void WriteVarLong(const long long int my_long, WriteContainer &container)
    {
        unsigned long long int value = my_long;
        do {
            unsigned char temp = (unsigned char)(value & 127);//0b01111111
            value >>= 7;
            if (value != 0)
            {
                temp |= 128;//0b10000000
            }
            container.push_back(temp);
        } while (value != 0);
    }

    std::string ReadString(ReadIterator &iter, size_t &length)
    {
        int size = ReadVarInt(iter, length);

        if (length < size)
        {
            throw(std::runtime_error("Not enough input in ReadString"));
        }
        else
        {
            std::string output = std::string(iter, iter + size);

            iter += size;
            length -= size;

            return output;
        }
    }

    void WriteString(const std::string &my_string, WriteContainer &container)
    {
        WriteVarInt(my_string.size(), container);
        container.insert(container.end(), my_string.begin(), my_string.end());
    }

    std::string ReadRawString(ReadIterator &iter, size_t &length, const int size)
    {
        if (length < size)
        {
            throw(std::runtime_error("Not enough input in ReadRawString"));
        }
        else
        {
            std::string output = std::string(iter, iter + size);

            iter += size;
            length -= size;

            return output;
        }
    }

    void WriteRawString(const std::string &s, WriteContainer &container)
    {
        container.insert(container.end(), s.begin(), s.end());
    }

    std::vector<unsigned char> ReadByteArray(ReadIterator &iter, size_t &length, const size_t &desired_length)
    {
        if (length < desired_length)
        {
            throw(std::runtime_error("Not enough input in ReadByteArray"));
        }
        else
        {
            std::vector<unsigned char> output(desired_length);
            std::copy(iter, iter + desired_length, output.begin());

            iter += desired_length;
            length -= desired_length;

            return output;
        }
    }

    void WriteByteArray(const std::vector<unsigned char> &my_array, WriteContainer &container)
    {
        container.insert(container.end(), my_array.begin(), my_array.end());
    }

    Position ReadPosition(ReadIterator &iter, size_t &length)
    {
        unsigned long long int value = ReadData<unsigned long long int>(iter, length);

        int x = value >> 38;
        if (x >= 33554432)
        {
            x -= 67108864;
        }

#if PROTOCOL_VERSION < 442
        int y = (value >> 26) & 0xFFF;
        if (y >= 2048)
        {
            y -= 4096;
        }
        int z = value << 38 >> 38;
        if (z >= 33554432)
        {
            z -= 67108864;
        }
#else
        int y = value & 0xFFF;
        if (y >= 2048)
        {
            y -= 4096;
        }
        int z = value << 26 >> 38;
        if (z >= 33554432)
        {
            z -= 67108864;
        }
#endif

        return Position(x, y, z);
    }

    void WritePosition(const Position &my_position, WriteContainer &container)
    {
#if PROTOCOL_VERSION < 442
        unsigned long long int value = (((long long int)my_position.x & 0x3FFFFFF) << 38) | (((long long int)my_position.y & 0xFFF) << 26) | ((long long int)my_position.z & 0x3FFFFFF);
#else
        unsigned long long int value = (((long long int)my_position.x & 0x3FFFFFF) << 38) | (((long long int)my_position.z & 0x3FFFFFF) << 12) | ((long long int)my_position.y & 0xFFF);
#endif
        WriteData<unsigned long long int>(value, container);
    }
} //Botcraft