#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"
#include "botcraft/Game/Enums.hpp"

#include "botcraft/Version.hpp"

#if PROTOCOL_VERSION > 493 
namespace Botcraft
{
    class AcknowledgePlayerDigging : public BaseMessage<AcknowledgePlayerDigging>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 498 // 1.14.4
            return 0x5C;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Acknowledge Player Digging";
        }

        const Position GetLocation() const
        {
            return location;
        }

        const int GetBlock() const
        {
            return block;
        }

        const PlayerDiggingStatus GetStatus() const
        {
            return status;
        }

        const bool GetSuccessful() const
        {
            return successful;
        }
    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            location = ReadPosition(iter, length);
            block = ReadVarInt(iter, length);
            status = (PlayerDiggingStatus)ReadVarInt(iter, length);
            successful = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            std::cerr << "Clientbound message" << std::endl;
        }

    private:
        Position location;
        int block;
        PlayerDiggingStatus status;
        bool successful;
    };
} //Botcraft

#endif