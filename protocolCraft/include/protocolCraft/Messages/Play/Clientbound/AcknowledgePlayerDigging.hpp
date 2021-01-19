#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

#if PROTOCOL_VERSION > 493 
namespace ProtocolCraft
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
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x07;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x07;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Acknowledge Player Digging";
        }

        void SetLocation(const NetworkPosition& location_)
        {
            location = location_;
        }

        void SetBlock(const int block_)
        {
            block = block_;
        }

        void SetStatus(const int status_)
        {
            status = status_;
        }

        void SetSuccessful(const bool successful_)
        {
            successful = successful_;
        }

        const NetworkPosition& GetLocation() const
        {
            return location;
        }

        const int GetBlock() const
        {
            return block;
        }

        const int GetStatus() const
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
            location.Read(iter, length);
            block = ReadVarInt(iter, length);
            status = ReadVarInt(iter, length);
            successful = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            location.Write(container);
            WriteVarInt(block, container);
            WriteVarInt(status, container);
            WriteData<bool>(successful, container);
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
        NetworkPosition location;
        int block;
        int status;
        bool successful;
    };
} //ProtocolCraft

#endif