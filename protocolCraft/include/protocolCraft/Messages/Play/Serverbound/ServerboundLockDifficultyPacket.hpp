#pragma once

#if PROTOCOL_VERSION > 463
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundLockDifficultyPacket : public BaseMessage<ServerboundLockDifficultyPacket>
    {
    public:
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x12;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Lock Difficulty";

        virtual ~ServerboundLockDifficultyPacket() override
        {

        }

        void SetLocked(const bool locked_)
        {
            locked = locked_;
        }


        const bool GetLocked() const
        {
            return locked;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            locked = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(locked, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["locked"] = locked;

            return output;
        }

    private:
        bool locked;

    };
} //ProtocolCraft
#endif
