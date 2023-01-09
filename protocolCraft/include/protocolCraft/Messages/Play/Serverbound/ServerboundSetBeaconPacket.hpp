#pragma once

#if PROTOCOL_VERSION > 385
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundSetBeaconPacket : public BaseMessage<ServerboundSetBeaconPacket>
    {
    public:
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x26;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x27;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Set Beacon";

        virtual ~ServerboundSetBeaconPacket() override
        {

        }

#if PROTOCOL_VERSION < 759
        void SetPrimary(const int primary_)
        {
            primary = primary_;
        }

        void SetSecondary(const int secondary_)
        {
            secondary = secondary_;
        }
#else
        void SetPrimary(const std::optional<int>& primary_)
        {
            primary = primary_;
        }

        void SetSecondary(const std::optional<int>& secondary_)
        {
            secondary = secondary_;
        }
#endif


#if PROTOCOL_VERSION < 759
        int GetPrimary() const
        {
            return primary;
        }

        int GetSecondary() const
        {
            return secondary;
        }
#else
        const std::optional<int>& GetPrimary() const
        {
            return primary;
        }

        const std::optional<int>& GetSecondary() const
        {
            return secondary;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 759
            primary = ReadData<VarInt>(iter, length);
            secondary = ReadData<VarInt>(iter, length);
#else
            primary = ReadOptional<VarInt>(iter, length);
            secondary = ReadOptional<VarInt>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 759
            WriteData<VarInt>(primary, container);
            WriteData<VarInt>(secondary, container);
#else
            WriteOptional<VarInt>(primary, container);
            WriteOptional<VarInt>(secondary, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 759
            output["primary"] = primary;
            output["secondary"] = secondary;
#else
            if (primary.has_value())
            {
                output["primary"] = primary.value();
            }
            if (secondary.has_value())
            {
                output["secondary"] = secondary.value();
            }
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 759
        int primary;
        int secondary;
#else
        std::optional<int> primary;
        std::optional<int> secondary;
#endif

    };
} //ProtocolCraft
#endif
