#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"
#include "botcraft/Game/Enums.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
{
    class ServerDifficulty : public BaseMessage<ServerDifficulty>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x0D;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x0D;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x0D;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x0E;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Server Difficulty";
        }

        const Difficulty GetDifficulty() const
        {
            return difficulty;
        }

#if PROTOCOL_VERSION >= 477 // 1.14
        const bool GetDifficultyLocked() const
        {
            return difficulty_locked;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            difficulty = (Difficulty)ReadData<unsigned char>(iter, length);
#if PROTOCOL_VERSION >= 477 // 1.14
            difficulty_locked = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            std::cerr << "Clientbound message" << std::endl;
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["difficulty"] = picojson::value((double)difficulty);
#if PROTOCOL_VERSION >= 477 // 1.14
            object["difficulty_locked"] = picojson::value(difficulty_locked);
#endif

            return value;
        }

    private:
        Difficulty difficulty;

#if PROTOCOL_VERSION >= 477 // 1.14
        bool difficulty_locked;
#endif
    };
} //Botcraft