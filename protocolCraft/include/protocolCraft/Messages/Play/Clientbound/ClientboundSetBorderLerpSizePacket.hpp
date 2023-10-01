#pragma once

#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderLerpSizePacket : public BaseMessage<ClientboundSetBorderLerpSizePacket>
    {
    public:
#if   PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x43;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x42;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x45;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x44;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x48;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x4A;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Border Lerp Size";

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


        double GetOldSize() const
        {
            return old_size;
        }

        double GetNewSize() const
        {
            return new_size;
        }

        long long int GetLerpTime() const
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

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["old_size"] = old_size;
            output["new_size"] = new_size;
            output["lerp_time"] = lerp_time;

            return output;
        }

    private:
        double old_size = 0.0;
        double new_size = 0.0;
        long long int lerp_time = 0;

    };
} //ProtocolCraft
#endif
