#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class UnloadChunk : public BaseMessage<UnloadChunk>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x1D;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x1F;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1D;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x1E;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x1D;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x1C;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Unload Chunk";
        }

        void SetChunkX(const int chunk_x_)
        {
            chunk_x = chunk_x_;
        }

        void SetChunkZ(const int chunk_z_)
        {
            chunk_z = chunk_z_;
        }

        const int GetChunkX() const
        {
            return chunk_x;
        }

        const int GetChunkZ() const
        {
            return chunk_z;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            chunk_x = ReadData<int>(iter, length);
            chunk_z = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<int>(chunk_x, container);
            WriteData<int>(chunk_z, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["chunk_x"] = picojson::value((double)chunk_x);
            object["chunk_z"] = picojson::value((double)chunk_z);

            return value;
        }

    private:
        int chunk_x;
        int chunk_z;
    };
} //ProtocolCraft