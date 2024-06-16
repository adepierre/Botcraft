#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <optional>
#include <vector>

namespace ProtocolCraft
{
    class HolderSet : public NetworkType
    {
    public:
        virtual ~HolderSet()
        {

        }


        const std::optional<Identifier>& GetKey() const
        {
            return key;
        }

        const std::vector<int>& GetContents() const
        {
            return contents;
        }


        auto& SetKey(const std::optional<Identifier>& key_)
        {
            key = key_;
            if (key.has_value())
            {
                contents.clear();
            }
            return *this;
        }

        auto& SetContents(const std::vector<int>& contents_)
        {
            contents = contents_;
            if (contents.size() > 0)
            {
                key = std::optional<Identifier>();
            }
            return *this;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            const int size = ReadData<VarInt>(iter, length) - 1;
            if (size == -1)
            {
                key = ReadData<Identifier>(iter, length);
            }
            else
            {
                contents = std::vector<int>(size);
                for (int i = 0; i < size; ++i)
                {
                    contents[i] = ReadData<VarInt>(iter, length);
                }
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            if (key.has_value())
            {
                WriteData<VarInt>(0, container);
                WriteData<Identifier>(key.value(), container);
            }
            else
            {
                WriteData<VarInt>(static_cast<int>(contents.size()) + 1, container);
                for (const int i : contents)
                {
                    WriteData<VarInt>(i, container);
                }
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            if (key.has_value())
            {
                output["key"] = key.value();
            }
            else
            {
                output["content"] = contents;
            }

            return output;
        }

    private:
        std::optional<Identifier> key;
        std::vector<int> contents;

    };
}
#endif
