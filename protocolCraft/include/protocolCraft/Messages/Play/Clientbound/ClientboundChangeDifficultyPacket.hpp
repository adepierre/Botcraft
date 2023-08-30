#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundChangeDifficultyPacket : public BaseMessage<ClientboundChangeDifficultyPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 || PROTOCOL_VERSION == 393 ||  \
      PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 ||  \
      PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 759 || PROTOCOL_VERSION == 760 ||  \
      PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x0C;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Change Difficulty";

        virtual ~ClientboundChangeDifficultyPacket() override
        {

        }

        void SetDifficulty(const int difficulty_)
        {
            difficulty = difficulty_;
        }

#if PROTOCOL_VERSION >= 477
        void SetLocked(const bool locked_)
        {
            locked = locked_;
        }
#endif

        int GetDifficulty() const
        {
            return difficulty;
        }

#if PROTOCOL_VERSION >= 477
        bool GetLocked() const
        {
            return locked;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            difficulty = ReadData<unsigned char>(iter, length);
#if PROTOCOL_VERSION >= 477
            locked = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<unsigned char>((unsigned char)difficulty, container);
#if PROTOCOL_VERSION >= 477
            WriteData<bool>(locked, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["difficulty"] = difficulty;
#if PROTOCOL_VERSION >= 477
            output["locked"] = locked;
#endif

            return output;
        }

    private:
        int difficulty = 0;

#if PROTOCOL_VERSION >= 477
        bool locked = false;
#endif
    };
} //ProtocolCraft
