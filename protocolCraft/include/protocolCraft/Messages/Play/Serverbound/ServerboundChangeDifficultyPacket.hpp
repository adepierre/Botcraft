#pragma once

#if PROTOCOL_VERSION > 463
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundChangeDifficultyPacket : public BaseMessage<ServerboundChangeDifficultyPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x02;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x02;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x02;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x02;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x02;
#elif PROTOCOL_VERSION == 757 // 1.18
            return 0x02;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Change Difficulty";
        }

        virtual ~ServerboundChangeDifficultyPacket() override
        {

        }

        void SetDifficulty(const char difficulty_)
        {
            difficulty = difficulty_;
        }


        const char GetDifficulty() const
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

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["difficulty"] = difficulty;

            return output;
        }

    private:
        char difficulty;

    };
} //ProtocolCraft
#endif
