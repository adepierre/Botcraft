#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION < 739
#include "protocolCraft/Types/Record.hpp"
#endif

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
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x0F;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x3B;
#else
    #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Multi Block change";
        }

#if PROTOCOL_VERSION < 739
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
#else
        void SetChunkSectionCoordinate(const long long int chunk_section_coordinate_)
        {
            chunk_section_coordinate = chunk_section_coordinate_;
        }

        void SetUnknown(const bool unknown_)
        {
            unknown = unknown_;
        }

        void SetArraySize(const int array_size_)
        {
            array_size = array_size_;
        }

        void SetData(const std::vector<long long int>& data_)
        {
            data = data_;
        }
#endif

#if PROTOCOL_VERSION < 739
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
#else
        const long long int GetChunkSectionCoordinate() const
        {
            return chunk_section_coordinate;
        }

        const bool GetUnknown() const
        {
            return unknown;
        }

        const int GetArraySize() const
        {
            return array_size;
        }

        const std::vector<long long int>& GetData() const
        {
            return data;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
#if PROTOCOL_VERSION < 739
            chunk_x = ReadData<int>(iter, length);
            chunk_z = ReadData<int>(iter, length);
            record_count = ReadVarInt(iter, length);

            records = std::vector<Record>(record_count);

            for (int i = 0; i < record_count; ++i)
            {
                records[i].Read(iter, length);
            }
#else
            chunk_section_coordinate = ReadData<long long int>(iter, length);
            unknown = ReadData<bool>(iter, length);
            array_size = ReadVarInt(iter, length);
            data = std::vector<long long int>(array_size);
            for (int i = 0; i < array_size; ++i)
            {
                data[i] = ReadVarLong(iter, length);
            }
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
#if PROTOCOL_VERSION < 739
            WriteData<int>(chunk_x, container);
            WriteData<int>(chunk_z, container);
            WriteVarInt(record_count, container);
            for (int i = 0; i < record_count; ++i)
            {
                records[i].Write(container);
            }
#else
            WriteData<long long int>(chunk_section_coordinate, container);
            WriteData<bool>(unknown, container);
            WriteVarInt(array_size, container);
            for (int i = 0; i < array_size; ++i)
            {
                WriteVarLong(data[i], container);
            }
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

#if PROTOCOL_VERSION < 739
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
#else
            object["chunk_section_coordinate"] = picojson::value((double)chunk_section_coordinate);
            object["unknown"] = picojson::value(unknown);
            object["array_size"] = picojson::value((double)array_size);
            object["data"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["data"].get<picojson::array>();
            array.reserve(data.size());

            for (int i = 0; i < data.size(); ++i)
            {
                array.push_back(picojson::value((double)data[i]));
            }
#endif

            return value;
        }

    private:
#if PROTOCOL_VERSION < 739
        int chunk_x;
        int chunk_z;
        int record_count;
        std::vector<Record> records;
#else
        long long int chunk_section_coordinate;
        bool unknown;
        int array_size;
        std::vector<long long int> data;
#endif
    };
}