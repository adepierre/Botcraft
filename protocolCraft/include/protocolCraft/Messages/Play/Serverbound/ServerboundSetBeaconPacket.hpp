#pragma once

#if PROTOCOL_VERSION > 385
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundSetBeaconPacket : public BaseMessage<ServerboundSetBeaconPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x20;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x22;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x22;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x23;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x24;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x24;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x24;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x26;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x27;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Beacon";
        }

        virtual ~ServerboundSetBeaconPacket() override
        {

        }

        void SetPrimary(const int primary_)
        {
            primary = primary_;
        }

        void SetSecondary(const int secondary_)
        {
            secondary = secondary_;
        }


        const int GetPrimary() const
        {
            return primary;
        }

        const int GetSecondary() const
        {
            return secondary;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 759
            primary = ReadData<VarInt>(iter, length);
            secondary = ReadData<VarInt>(iter, length);
#else
            const bool has_primary = ReadData<bool>(iter, length);
            primary = 0;
            if (has_primary)
            {
                primary = ReadData<VarInt>(iter, length);
            }
            const bool has_secondary = ReadData<bool>(iter, length);
            secondary = 0;
            if (has_secondary)
            {
                secondary = ReadData<VarInt>(iter, length);
            }
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 759
            WriteData<VarInt>(primary, container);
            WriteData<VarInt>(secondary, container);
#else
            WriteData<bool>(primary > 0, container);
            if (primary > 0)
            {
                WriteData<VarInt>(primary, container);
            }
            WriteData<bool>(secondary > 0, container);
            if (secondary > 0)
            {
                WriteData<VarInt>(secondary, container);
            }
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

#if PROTOCOL_VERSION < 759
            output["primary"] = primary;
            output["secondary"] = secondary;
#else
            if (primary > 0)
            {
                output["primary"] = primary;
            }
            if (secondary > 0)
            {
                output["secondary"] = secondary;
            }
#endif

            return output;
        }

    private:
        int primary;
        int secondary;

    };
} //ProtocolCraft
#endif
