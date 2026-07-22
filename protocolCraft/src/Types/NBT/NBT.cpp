#include <iterator>
#include <fstream>
#include <utility>

#include "protocolCraft/Types/NBT/NBT.hpp"
#include "protocolCraft/Utilities/GZip.hpp"

namespace ProtocolCraft
{
    namespace NBT
    {
        UnnamedValue::UnnamedValue()
        {

        }

        UnnamedValue::UnnamedValue(const Value& named) : Tag(named)
        {

        }

        UnnamedValue::UnnamedValue(Value&& named) : Tag(std::move(named))
        {

        }

        UnnamedValue::~UnnamedValue()
        {

        }

        void UnnamedValue::ReadImpl(ReadIterator& iter, size_t& length)
        {
            Tag::ReadUnnamedImpl(iter, length);
        }

        void UnnamedValue::WriteImpl(WriteContainer& container) const
        {
            Tag::WriteUnnamedImpl(container);
        }


#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        UntrustedValue::UntrustedValue()
        {

        }

        UntrustedValue::UntrustedValue(const Value& named) : Tag(named)
        {

        }

        UntrustedValue::UntrustedValue(Value&& named) : Tag(std::move(named))
        {

        }

        UntrustedValue::~UntrustedValue()
        {

        }

        void UntrustedValue::ReadImpl(ReadIterator& iter, size_t& length)
        {
            // Untrusted == size prefixed
            const int size = ReadData<VarInt>(iter, length);
            Tag::ReadUnnamedImpl(iter, length);
        }

        void UntrustedValue::WriteImpl(WriteContainer& container) const
        {
            // Untrusted == size prefixed
            std::vector<unsigned char> temp_container;
            Tag::WriteUnnamedImpl(temp_container);
            WriteData<VarInt>(static_cast<int>(temp_container.size()), container);
            WriteByteArray(temp_container, container);
        }
#endif


        Value::Value()
        {

        }

        Value::Value(const UnnamedValue& unnamed) : Tag(unnamed)
        {

        }

        Value::Value(UnnamedValue&& unnamed) : Tag(std::move(unnamed))
        {

        }

#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        Value::Value(const UntrustedValue& untrusted) : Tag(untrusted)
        {

        }

        Value::Value(UntrustedValue&& untrusted) : Tag(std::move(untrusted))
        {

        }
#endif

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
            // Check for GZIP minimal header size and magic number
            if (length > 10 && *iter == 0x1F && *(iter + 1) == 0x8B)
            {
                const std::vector<unsigned char> decompressed = ExtractGZip(iter, length);
                ReadIterator decomp_iter = decompressed.begin();
                size_t decomp_length = decompressed.size();
                Tag::ReadImpl(decomp_iter, decomp_length);
            }
            else
            {
                Tag::ReadImpl(iter, length);
            }

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
