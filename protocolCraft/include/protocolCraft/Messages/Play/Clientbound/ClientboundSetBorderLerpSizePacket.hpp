#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderLerpSizePacket : public BaseMessage<ClientboundSetBorderLerpSizePacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x43;
#elif PROTOCOL_VERSION == 757 // 1.18
            return 0x43;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Border Lerp Size";
        }

        virtual ~ClientboundSetBorderLerpSizePacket() override
        {

        }


        void SetOldSize(const double old_size_)
        {
            old_size = old_size_;
        }

        void SetNewSize(const double new_size_)
        {
            new_size = new_size_;
        }

        void SetLerpTime(const long long int lerp_time_)
        {
            lerp_time = lerp_time_;
        }


        const double GetOldSize() const
        {
            return old_size;
        }

        const double GetNewSize() const
        {
            return new_size;
        }

        const long long int GetLerpTime() const
        {
            return lerp_time;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            old_size = ReadData<double>(iter, length);
            new_size = ReadData<double>(iter, length);
            lerp_time = ReadData<VarLong>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<double>(old_size, container);
            WriteData<double>(new_size, container);
            WriteData<VarLong>(lerp_time, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["old_size"] = old_size;
            output["new_size"] = new_size;
            output["lerp_time"] = lerp_time;

            return output;
        }

    private:
        double old_size;
        double new_size;
        long long int lerp_time;

    };
} //ProtocolCraft
#endif