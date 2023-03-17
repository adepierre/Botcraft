#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPlayerInputPacket : public BaseMessage<ServerboundPlayerInputPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x1A;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 762 // 1.19.4
static constexpr int packet_id = 0x1F;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Player Input";

        virtual ~ServerboundPlayerInputPacket() override
        {

        }

        void SetXxa(const float xxa_)
        {
            xxa = xxa_;
        }

        void SetZza(const float zza_)
        {
            zza = zza_;
        }

        void SetFlags(const unsigned char flags_)
        {
            flags = flags_;
        }


        float GetXxa() const
        {
            return xxa;
        }

        float GetZza() const
        {
            return zza;
        }

        unsigned char GetFlags() const
        {
            return flags;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            xxa = ReadData<float>(iter, length);
            zza = ReadData<float>(iter, length);
            flags = ReadData<unsigned char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<float>(xxa, container);
            WriteData<float>(zza, container);
            WriteData<unsigned char>(flags, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["xxa"] = xxa;
            output["zza"] = zza;
            output["flags"] = flags;

            return output;
        }

    private:
        float xxa;
        float zza;
        unsigned char flags;

    };
} //ProtocolCraft
