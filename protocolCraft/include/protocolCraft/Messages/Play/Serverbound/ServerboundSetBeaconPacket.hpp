#pragma once

#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundSetBeaconPacket : public BaseMessage<ServerboundSetBeaconPacket>
    {
    public:
#if   PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */ || PROTOCOL_VERSION == 755 /* 1.17 */ ||  \
      PROTOCOL_VERSION == 756 /* 1.17.1 */ || PROTOCOL_VERSION == 757 /* 1.18/.1 */ ||  \
      PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x26;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */ || PROTOCOL_VERSION == 761 /* 1.19.3 */ ||  \
      PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x27;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Beacon";

        virtual ~ServerboundSetBeaconPacket() override
        {

        }

#if PROTOCOL_VERSION < 759 /* < 1.19 */
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


#if PROTOCOL_VERSION < 759 /* < 1.19 */
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
#if PROTOCOL_VERSION < 759 /* < 1.19 */
            primary = ReadData<VarInt>(iter, length);
            secondary = ReadData<VarInt>(iter, length);
#else
            primary = ReadOptional<VarInt>(iter, length);
            secondary = ReadOptional<VarInt>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
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

#if PROTOCOL_VERSION < 759 /* < 1.19 */
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
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        int primary = 0;
        int secondary = 0;
#else
        std::optional<int> primary;
        std::optional<int> secondary;
#endif

    };
} //ProtocolCraft
#endif
