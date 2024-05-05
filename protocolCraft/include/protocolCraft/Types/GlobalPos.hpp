#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class GlobalPos : public NetworkType
    {
    public:
        virtual ~GlobalPos() override
        {

        }

        void SetDimension(const Identifier& dimension_)
        {
            dimension = dimension_;
        }

        void SetPos(const NetworkPosition& pos_)
        {
            pos = pos_;
        }


        const Identifier& GetDimension() const
        {
            return dimension;
        }

        const NetworkPosition& GetPos() const
        {
            return pos;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            dimension = ReadData<Identifier>(iter, length);
            pos = ReadData<NetworkPosition>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Identifier>(dimension, container);
            WriteData<NetworkPosition>(pos, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["dimension"] = dimension;
            output["pos"] = pos;


            return output;
        }

    private:
        Identifier dimension;
        NetworkPosition pos;
    };
}
#endif
