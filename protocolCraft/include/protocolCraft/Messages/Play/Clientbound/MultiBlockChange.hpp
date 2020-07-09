#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Record.hpp"

namespace ProtocolCraft
{
    class MultiBlockChange : public BaseMessage<MultiBlockChange>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x10;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x0F;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x0F;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x10;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
            return 0x0F;
#else
    #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Multi Block change";
        }

        void SetChunkX(const int chunk_x_)
        {
            chunk_x = chunk_x_;
        }

        void SetChunkZ(const int chunk_z_)
        {
            chunk_z = chunk_z_;
        }

        void SetRecordCount(const int record_count_)
        {
            record_count = record_count_;
        }

        void SetRecords(const std::vector<Record>& records_)
        {
            records = records_;
        }

        const int GetChunkX() const
        {
            return chunk_x;
        }

        const int GetChunkZ() const
        {
            return chunk_z;
        }

        const int GetRecordCount() const
        {
            return record_count;
        }

        const std::vector<Record>& GetRecords() const
        {
            return records;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            chunk_x = ReadData<int>(iter, length);
            chunk_z = ReadData<int>(iter, length);
            record_count = ReadVarInt(iter, length);

            records = std::vector<Record>(record_count);

            for (int i = 0; i < record_count; ++i)
            {
                records[i].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<int>(chunk_x, container);
            WriteData<int>(chunk_z, container);
            WriteVarInt(record_count, container);
            for (int i = 0; i < record_count; ++i)
            {
                records[i].Write(container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["chunk_x"] = picojson::value((double)chunk_x);
            object["chunk_z"] = picojson::value((double)chunk_z);
            object["record_count"] = picojson::value((double)record_count);

            object["records"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["records"].get<picojson::array>();
            array.reserve(records.size());

            for (int i = 0; i < records.size(); ++i)
            {
                array.push_back(records[i].Serialize());
            }

            return value;
        }

    private:
        int chunk_x;
        int chunk_z;
        int record_count;
        std::vector<Record> records;
    };
}