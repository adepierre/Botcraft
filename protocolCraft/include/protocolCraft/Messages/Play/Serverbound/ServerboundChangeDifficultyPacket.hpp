#pragma once

#if PROTOCOL_VERSION > 463
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundChangeDifficultyPacket : public BaseMessage<ServerboundChangeDifficultyPacket>
    {
    public:
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x02;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x02;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x02;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x02;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x02;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x02;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x02;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x02;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x02;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x02;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Change Difficulty";

        virtual ~ServerboundChangeDifficultyPacket() override
        {

        }

        void SetDifficulty(const char difficulty_)
        {
            difficulty = difficulty_;
        }


        char GetDifficulty() const
        {
            return difficulty;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            difficulty = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(difficulty, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["difficulty"] = difficulty;

            return output;
        }

    private:
        char difficulty;

    };
} //ProtocolCraft
#endif
