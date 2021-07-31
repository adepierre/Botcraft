#include <stdexcept>

#include "protocolCraft/BinaryReadWrite.hpp"

namespace ProtocolCraft
{
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

    UUID ReadUUID(ReadIterator& iter, size_t& length)
    {
        return ReadRawString(iter, length, 16);
    }

    void WriteUUID(const UUID& s, WriteContainer& container)
    {
        WriteRawString(s, container);
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

    template<>
    std::string ReadData(ReadIterator& iter, size_t& length)
    {
        int size = ReadData<VarInt>(iter, length);

        if (length < size)
        {
            throw(std::runtime_error("Not enough input in ReadData<std::string>"));
        }
        else
        {
            std::string output = std::string(iter, iter + size);

            iter += size;
            length -= size;

            return output;
        }
    }

    template<>
    VarInt ReadData(ReadIterator& iter, size_t& length)
    {
        int numRead = 0;
        int result = 0;

        unsigned char read;

        do
        {
            if (numRead >= length)
            {
                throw(std::runtime_error("Not enough input in ReadData<VarInt>"));
            }

            read = *(iter + numRead);

            int value = (read & 127);//0b01111111
            result |= (value << (7 * numRead));

            numRead++;

            if (numRead > 5)
            {
                throw(std::runtime_error("VarInt is too big in ReadData<VarInt>"));
            }

        } while ((read & 128) != 0);//0b10000000

        iter += numRead;
        length -= numRead;

        return result;
    }

    template<>
    VarLong ReadData(ReadIterator& iter, size_t& length)
    {
        int numRead = 0;
        long long int result = 0;

        unsigned char read;

        do
        {
            if (numRead >= length)
            {
                throw(std::runtime_error("Not enough input in ReadData<VarLong>"));
            }

            read = *(iter + numRead);

            long long int value = (read & 127);//0b01111111
            result |= (value << (7 * numRead));

            numRead++;

            if (numRead > 10)
            {
                throw(std::runtime_error("VarLong is too big in ReadData<VarLong>"));
            }

        } while ((read & 128) != 0);//0b10000000

        iter += numRead;
        length -= numRead;

        return result;
    }

    template<>
    void WriteData(const std::string& value, WriteContainer& container)
    {
        WriteData<VarInt>(value.size(), container);
        container.insert(container.end(), value.begin(), value.end());
    }

    template<>
    void WriteData(const VarInt &value, WriteContainer& container)
    {
        unsigned int val = value;
        do {
            unsigned char temp = (unsigned char)(val & 127);//0b01111111
            val >>= 7;
            if (val != 0)
            {
                temp |= 128;//0b10000000
            }
            container.push_back(temp);
        } while (val != 0);
    }

    template<>
    void WriteData(const VarLong &value, WriteContainer& container)
    {
        unsigned long long int val = value;
        do {
            unsigned char temp = (unsigned char)(val & 127);//0b01111111
            val >>= 7;
            if (val != 0)
            {
                temp |= 128;//0b10000000
            }
            container.push_back(temp);
        } while (val != 0);
    }
} //ProtocolCraft
