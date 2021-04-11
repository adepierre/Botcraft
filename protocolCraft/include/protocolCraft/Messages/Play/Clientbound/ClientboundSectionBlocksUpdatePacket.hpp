#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION < 739
#include "protocolCraft/Types/Record.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSectionBlocksUpdatePacket : public BaseMessage<ClientboundSectionBlocksUpdatePacket>
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
            return "Section Blocks Update";
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
        void SetSectionPos(const long long int section_pos_)
        {
            section_pos = section_pos_;
        }

        void SetSuppressLightUpdates(const bool suppress_light_updates_)
        {
            suppress_light_updates = suppress_light_updates_;
        }

        void SetPositions(const std::vector<short>& positions_)
        {
            positions = positions_;
        }

        void SetStates(const std::vector<int>& states_)
        {
            states = states_;
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
        const long long int GetSectionPos() const
        {
            return section_pos;
        }

        const bool GetSuppressLightUpdates() const
        {
            return suppress_light_updates;
        }

        const std::vector<short>& GetPositions() const
        {
            return positions;
        }

        const std::vector<int>& GetStates() const
        {
            return states;
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
            section_pos = ReadData<long long int>(iter, length);
            suppress_light_updates = ReadData<bool>(iter, length);
            int data_size = ReadVarInt(iter, length);
            positions = std::vector<short>(data_size);
            states = std::vector<int>(data_size);
            for (int i = 0; i < data_size; ++i)
            {
                long long int data = ReadVarLong(iter, length);
                positions[i] = data & 0xFFl;
                states[i] = data >> 12;
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
            WriteData<long long int>(section_pos, container);
            WriteData<bool>(suppress_light_updates, container);
            WriteVarInt(positions.size(), container);
            for (int i = 0; i < positions.size(); ++i)
            {
                WriteVarLong((states[i] << 12) | positions[i], container);
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
            object["section_pos"] = picojson::value((double)section_pos);
            object["suppress_light_updates"] = picojson::value(suppress_light_updates);
            object["positions"] = picojson::value(picojson::array_type, false);
            picojson::array& array_positions = object["positions"].get<picojson::array>();
            array_positions.reserve(positions.size());

            for (int i = 0; i < positions.size(); ++i)
            {
                array_positions.push_back(picojson::value((double)positions[i]));
            }

            picojson::array& array_states = object["states"].get<picojson::array>();
            array_states.reserve(states.size());

            for (int i = 0; i < states.size(); ++i)
            {
                array_states.push_back(picojson::value((double)states[i]));
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
        long long int section_pos;
        bool suppress_light_updates;
        std::vector<short> positions;
        std::vector<int> states;
#endif
    };
}