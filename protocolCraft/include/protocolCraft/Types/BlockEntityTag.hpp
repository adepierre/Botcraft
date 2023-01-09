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

        void SetEntries(const std::vector<int>& entries_)
        {
            entries = entries_;
        }


        const Identifier& GetTagName() const
        {
            return tag_name;
        }

        const std::vector<int>& GetEntries() const
        {
            return entries;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            tag_name = ReadData<Identifier>(iter, length);
            entries = ReadVector<int>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return static_cast<int>(ReadData<VarInt>(i, l));
                }
            );
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Identifier>(tag_name, container);
            WriteVector<int>(entries, container,
                [](const int& i, WriteContainer& c)
                {
                    WriteData<VarInt>(i, c);
                }
            );
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["tag_name"] = tag_name.Serialize();
            output["entries"] = entries;

            return output;
        }

    private:
        Identifier tag_name;
        std::vector<int> entries;
    };
} // ProtocolCraft
#endif
