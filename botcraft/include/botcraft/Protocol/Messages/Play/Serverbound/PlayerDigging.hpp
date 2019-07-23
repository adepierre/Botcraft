#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
{
    enum class PlayerDiggingFace
    {
        Bottom = 0, // -Y
        Top,        // +Y
        North,      // -Z
        South,      // +Z
        West,       // -X
        East        // +X
    };

    class PlayerDigging : public BaseMessage<PlayerDigging>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x14;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x18;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1A;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Digging";
        }

        void SetStatus(const PlayerDiggingStatus status_)
        {
            status = status_;
        }

        void SetLocation(const Position &pos)
        {
            location = pos;
        }

        void SetFace(const PlayerDiggingFace f)
        {
            face = f;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            std::cerr << "Severbound message" << std::endl;
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVarInt((int)status, container);
            WritePosition(location, container);
            WriteData<char>((char)face, container);
        }

    private:
        PlayerDiggingStatus status;
        Position location;
        PlayerDiggingFace face;
    };
} //Botcraft