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
            tag_name.Read(iter, length);
            count = ReadData<VarInt>(iter, length);
            entries = std::vector<int>(count);
            for (int i = 0; i < count; ++i)
            {
                entries[i] = ReadData<VarInt>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            tag_name.Write(container);
            WriteData<VarInt>(count, container);
            for (int i = 0; i < count; ++i)
            {
                WriteData<VarInt>(entries[i], container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["tag_name"] = tag_name.Serialize();
            object["count"] = picojson::value((double)count);
            object["entries"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["entries"].get<picojson::array>();

            for (int i = 0; i < count; ++i)
            {
                array.push_back(picojson::value((double)entries[i]));
            }

            return value;
        }

    private:
        Identifier tag_name;
        int count;
        std::vector<int> entries;
    };
} // ProtocolCraft
#endif
