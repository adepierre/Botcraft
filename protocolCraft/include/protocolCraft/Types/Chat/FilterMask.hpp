#if PROTOCOL_VERSION > 759 /* > 1.19 */
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


        int GetType() const
        {
            return type;
        }

        const std::vector<long long int>& GetMask() const
        {
            return mask;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            type = ReadData<VarInt>(iter, length);
            if (type == 2)
            {
                mask = ReadData<std::vector<long long int>>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(type, container);
            if (type == 2)
            {
                WriteData<std::vector<long long int>>(mask, container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["type"] = type;
            if (type == 2)
            {
                output["mask"] = mask;
            }

            return output;
        }

    private:
        int type = 0;
        std::vector<long long int> mask;
    };
}
#endif
