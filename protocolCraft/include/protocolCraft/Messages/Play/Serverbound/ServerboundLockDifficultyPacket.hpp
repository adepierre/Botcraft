#pragma once

#if PROTOCOL_VERSION > 463
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundLockDifficultyPacket : public BaseMessage<ServerboundLockDifficultyPacket>
    {
    public:
#if   PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498 || PROTOCOL_VERSION == 573 ||  \
      PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x13;
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


        bool GetLocked() const
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

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["locked"] = locked;

            return output;
        }

    private:
        bool locked = false;

    };
} //ProtocolCraft
#endif
