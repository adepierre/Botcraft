#pragma once

#if PROTOCOL_VERSION > 756
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"
#include "protocolCraft/Types/ClientboundLevelChunkPacketData.hpp"
#include "protocolCraft/Types/ClientboundLightUpdatePacketData.hpp"

namespace ProtocolCraft
{

    class ClientboundLevelChunkWithLightPacket : public BaseMessage<ClientboundLevelChunkWithLightPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x22;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x1F;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x21;
#elif PROTOCOL_VERSION == 761 // 1.19.3
            return 0x20;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Level Chunk With Light";
        }

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


        const int GetX() const
        {
            return x;
        }

        const int GetZ() const
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

            chunk_data.Read(iter, length);
            light_data.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<int>(x, container);
            WriteData<int>(z, container);

            chunk_data.Write(container);
            light_data.Write(container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["x"] = x;
            output["z"] = z;

            output["chunk_data"] = chunk_data.Serialize();
            output["light_data"] = light_data.Serialize();

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
