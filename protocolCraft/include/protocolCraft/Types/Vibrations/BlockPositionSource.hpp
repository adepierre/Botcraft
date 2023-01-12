#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/Types/Vibrations/PositionSource.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class BlockPositionSource : public PositionSource
    {
    public:
        virtual ~BlockPositionSource() override
        {

        }

        void SetPos(const NetworkPosition& pos_)
        {
            pos = pos_;
        }


        const NetworkPosition& GetPos() const
        {
            return pos;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            pos = ReadData<NetworkPosition>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<NetworkPosition>(pos, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["pos"] = pos;

            return output;
        }

    private:
        NetworkPosition pos;
    };
}
#endif
