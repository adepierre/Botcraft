#pragma once

#if PROTOCOL_VERSION > 463
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class SetDifficulty : public BaseMessage<SetDifficulty>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x02;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x02;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Difficulty";
        }

        void SetNewDifficulty(const char new_difficulty_)
        {
            new_difficulty = new_difficulty_;
        }


        const char GetNewDifficulty() const
        {
            return new_difficulty;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            new_difficulty = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(new_difficulty, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["new_difficulty"] = picojson::value((double)new_difficulty);

            return value;
        }

    private:
        char new_difficulty;

    };
} //ProtocolCraft
#endif
