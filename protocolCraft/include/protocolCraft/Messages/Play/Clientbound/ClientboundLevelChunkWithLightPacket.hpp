#pragma once

#if PROTOCOL_VERSION > 756
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/ClientboundLevelChunkPacketData.hpp"
#include "protocolCraft/Types/ClientboundLightUpdatePacketData.hpp"

namespace ProtocolCraft
{

    class ClientboundLevelChunkWithLightPacket : public BaseMessage<ClientboundLevelChunkWithLightPacket>
    {
    public:
#if PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x21;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 763 // 1.20
        static constexpr int packet_id = 0x24;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Level Chunk With Light";

        virtual ~ClientboundLevelChunkWithLightPacket() override
        {

        }
        
        void SetX(const int x_)
        {
            x = x_;
        }

        void SetZ(const int z_)
        {
            z = z_;
        }

        void SetChunkData(const ClientboundLevelChunkPacketData& chunk_data_)
        {
            chunk_data = chunk_data_;
        }

        void SetLightData(const ClientboundLightUpdatePacketData& light_data_)
        {
            light_data = light_data_;
        }


        int GetX() const
        {
            return x;
        }

        int GetZ() const
        {
            return z;
        }

        const ClientboundLevelChunkPacketData& GetChunkData() const
        {
            return chunk_data;
        }

        const ClientboundLightUpdatePacketData& GetLightData() const
        {
            return light_data;
        }

    protected:

        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            x = ReadData<int>(iter, length);
            z = ReadData<int>(iter, length);

            chunk_data = ReadData<ClientboundLevelChunkPacketData>(iter, length);
            light_data = ReadData<ClientboundLightUpdatePacketData>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<int>(x, container);
            WriteData<int>(z, container);

            WriteData<ClientboundLevelChunkPacketData>(chunk_data, container);
            WriteData<ClientboundLightUpdatePacketData>(light_data, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["x"] = x;
            output["z"] = z;
            output["chunk_data"] = chunk_data;
            output["light_data"] = light_data;

            return output;
        }

    private:
        int x;
        int z;
        ClientboundLevelChunkPacketData chunk_data;
        ClientboundLightUpdatePacketData light_data;
    };
} //ProtocolCraft
#endif
