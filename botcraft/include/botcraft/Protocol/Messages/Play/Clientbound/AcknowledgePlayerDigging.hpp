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
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x08;
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

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["location"] = location.Serialize();
            object["block"] = picojson::value((double)block);
            object["status"] = picojson::value((double)status);
            object["successful"] = picojson::value(successful);

            return value;
        }

    private:
        Position location;
        int block;
        PlayerDiggingStatus status;
        bool successful;
    };
} //Botcraft

#endif