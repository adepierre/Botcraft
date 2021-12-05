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

        void SetPackedXZ(const int packed_XZ_)
        {
            packed_XZ = packed_XZ_;
        }

        void SetY(const int y_)
        {
            y = y_;
        }

        void SetType(const int type_)
        {
            type = type_;
        }

        void SetTag(const NBT& tag_)
        {
            tag = tag_;
        }


        const int GetPackedXZ() const
        {
            return packed_XZ;
        }

        const int GetY() const
        {
            return y;
        }

        const int GetType() const
        {
            return type;
        }

        const NBT& GetTag() const
        {
            return tag;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {

        }

        virtual void WriteImpl(WriteContainer& container) const override
        {

        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["packed_XZ"] = packed_XZ;
            output["y"] = y;
            output["type"] = type;
            output["tag"] = tag.Serialize();

            return output;
        }

    private:
        int packed_XZ;
        int y;
        int type;
        NBT tag;
    };
} // ProtocolCraft
#endif
