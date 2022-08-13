#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPlayerInputPacket : public BaseMessage<ServerboundPlayerInputPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x16;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x1A;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1C;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x1C;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x1D;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x1D;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x1C;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x1C;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x1E;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x1F;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Input";
        }

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


        const float GetXxa() const
        {
            return xxa;
        }

        const float GetZza() const
        {
            return zza;
        }

        const unsigned char GetFlags() const
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

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

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