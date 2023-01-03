#if PROTOCOL_VERSION > 759
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class FilterMask : public NetworkType
    {
    public:
        virtual ~FilterMask() override
        {

        }

        void SetType(const int type_)
        {
            type = type_;
        }

        void SetMask(const std::vector<long long int>& mask_)
        {
            mask = mask_;
        }


        const int GetType() const
        {
            return type;
        }

        const std::vector<long long int>& GetMask() const
        {
            return mask;
        }


    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            type = ReadData<VarInt>(iter, length);
            if (type == 2)
            {
                mask = ReadVector<long long int>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(type, container);
            if (type == 2)
            {
                WriteVector<long long int>(mask, container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["type"] = type;
            if (type == 2)
            {
                output["mask"] = mask;
            }

            return output;
        }

    private:
        int type;
        std::vector<long long int> mask;
    };
}
#endif
