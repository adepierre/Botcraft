#pragma once

#if PROTOCOL_VERSION > 348

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft 
{
    class BlockEntityTag : public NetworkType
    {
    public:
        virtual ~BlockEntityTag() override
        {

        }

        void SetTagName(const Identifier& tag_name_)
        {
            tag_name = tag_name_;
        }

        void SetCount(const int count_)
        {
            count = count_;
        }

        void SetEntries(const std::vector<int>& entries_)
        {
            entries = entries_;
        }


        const Identifier& GetTagName() const
        {
            return tag_name;
        }

        const int GetCount() const
        {
            return count;
        }

        const std::vector<int>& GetEntries() const
        {
            return entries;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            tag_name = ReadData<Identifier>(iter, length);
            count = ReadData<VarInt>(iter, length);
            entries = std::vector<int>(count);
            for (int i = 0; i < count; ++i)
            {
                entries[i] = ReadData<VarInt>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Identifier>(tag_name, container);
            WriteData<VarInt>(count, container);
            for (int i = 0; i < count; ++i)
            {
                WriteData<VarInt>(entries[i], container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["tag_name"] = tag_name.Serialize();
            output["count"] = count;
            output["entries"] = entries;

            return output;
        }

    private:
        Identifier tag_name;
        int count;
        std::vector<int> entries;
    };
} // ProtocolCraft
#endif
