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

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["pos"] = pos.Serialize();

            return output;
        }

    private:
        NetworkPosition pos;
    };
}
#endif
