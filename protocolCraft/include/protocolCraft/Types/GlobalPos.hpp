#if PROTOCOL_VERSION > 758
#pragma once

#include <string>

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
            dimension.Read(iter, length);
            pos.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            dimension.Write(container);
            pos.Write(container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["dimension"] = dimension.Serialize();
            output["pos"] = pos.Serialize();


            return output;
        }

    private:
        Identifier dimension;
        NetworkPosition pos;
    };
}
#endif
