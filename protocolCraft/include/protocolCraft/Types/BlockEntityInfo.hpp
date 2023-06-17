#pragma once

#if PROTOCOL_VERSION > 756
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft 
{
    class BlockEntityInfo : public NetworkType
    {
    public:
        virtual ~BlockEntityInfo() override
        {

        }

        void SetPackedXZ(const unsigned char packed_XZ_)
        {
            packed_XZ = packed_XZ_;
        }

        void SetY(const short y_)
        {
            y = y_;
        }

        void SetType(const int type_)
        {
            type = type_;
        }

        void SetTag(const NBT::Value& tag_)
        {
            tag = tag_;
        }


        unsigned char GetPackedXZ() const
        {
            return packed_XZ;
        }

        short GetY() const
        {
            return y;
        }

        int GetType() const
        {
            return type;
        }

        const NBT::Value& GetTag() const
        {
            return tag;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            packed_XZ = ReadData<unsigned char>(iter, length);
            y = ReadData<short>(iter, length);
            type = ReadData<VarInt>(iter, length);
            tag = ReadData<NBT::Value>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<unsigned char>(packed_XZ, container);
            WriteData<short>(y, container);
            WriteData<VarInt>(type, container);
            WriteData<NBT::Value>(tag, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["packed_XZ"] = packed_XZ;
            output["y"] = y;
            output["type"] = type;
            output["tag"] = tag;

            return output;
        }

    private:
        unsigned char packed_XZ = 0;
        short y = 0;
        int type = 0;
        NBT::Value tag;
    };
} // ProtocolCraft
#endif
