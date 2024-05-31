#include "protocolCraft/BinaryReadWrite.hpp"

namespace ProtocolCraft
{
    std::string ReadRawString(ReadIterator& iter, size_t& length, const size_t size)
    {
        if (length < size)
        {
            throw std::runtime_error("Not enough input in ReadRawString");
        }
        else
        {
            std::string output = std::string(iter, iter + size);

            iter += size;
            length -= size;

            return output;
        }
    }

    void WriteRawString(const std::string& s, WriteContainer& container)
    {
        container.insert(container.end(), s.begin(), s.end());
    }

    std::vector<unsigned char> ReadByteArray(ReadIterator& iter, size_t& length, const size_t desired_length)
    {
        if (length < desired_length)
        {
            throw std::runtime_error("Not enough input in ReadByteArray");
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

    void WriteByteArray(const std::vector<unsigned char>& my_array, WriteContainer& container)
    {
        container.insert(container.end(), my_array.begin(), my_array.end());
    }

    void WriteByteArray(const unsigned char* data, const size_t length, WriteContainer& container)
    {
        container.insert(container.end(), data, data + length);
    }
} //ProtocolCraft
