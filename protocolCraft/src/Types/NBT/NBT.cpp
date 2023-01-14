#include <iterator>
#include <fstream>

#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{
    namespace NBT
    {
        Value::Value()
        {

        }

        Value::~Value()
        {

        }

        bool Value::HasData() const
        {
            return !is<TagEnd>();
        }

        std::istream& operator>>(std::istream& is, Value& v)
        {
            std::vector<unsigned char> file_content = std::vector<unsigned char>(
                std::istream_iterator<unsigned char>(is),
                std::istream_iterator<unsigned char>()
            );
            ReadIterator iter = file_content.begin();
            size_t length = file_content.size();

            v = ReadData<Value>(iter, length);

            return is;
        }

        void Value::ReadImpl(ReadIterator& iter, size_t& length)
        {
            Tag::ReadImpl(iter, length);

            if (is<TagEnd>())
            {
                return;
            }

            if (!is<TagCompound>())
            {
                throw std::runtime_error("Error reading NBT value, not starting with compound");
            }
        }
    }
}
