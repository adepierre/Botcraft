#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class SetExperience : public BaseMessage<SetExperience>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x40;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x43;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x47;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x48;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x48;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 // 1.16.2, 1.16.3
            return 0x48;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Experience";
        }

        void SetExperienceBar(const float experience_bar_)
        {
            experience_bar = experience_bar_;
        }

        void SetLevel(const int level_)
        {
            level = level_;
        }

        void SetTotalExperience(const int total_experience_)
        {
            total_experience = total_experience_;
        }


        const float GetExperienceBar() const
        {
            return experience_bar;
        }

        const int GetLevel() const
        {
            return level;
        }

        const int GetTotalExperience() const
        {
            return total_experience;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            experience_bar = ReadData<float>(iter, length);
            level = ReadVarInt(iter, length);
            total_experience = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<float>(experience_bar, container);
            WriteVarInt(level, container);
            WriteVarInt(total_experience, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["experience_bar"] = picojson::value((double)experience_bar);
            object["level"] = picojson::value((double)level);
            object["total_experience"] = picojson::value((double)total_experience);

            return value;
        }

    private:
        float experience_bar;
        int level;
        int total_experience;

    };
} //ProtocolCraft