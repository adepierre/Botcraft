#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class BlockBreakAnimation : public BaseMessage<BlockBreakAnimation>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x08;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x08;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x08;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x09;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x08;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 // 1.16.2, 1.16.3
            return 0x08;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Block Break Animation";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetLocation(const NetworkPosition& location_)
        {
            location = location_;
        }

        void SetDestroyStage(const char destroy_stage_)
        {
            destroy_stage = destroy_stage_;
        }


        const int GetEntityId() const
        {
            return entity_id;
        }

        const NetworkPosition& GetLocation() const
        {
            return location;
        }

        const char GetDestroyStage() const
        {
            return destroy_stage;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadVarInt(iter, length);
            location.Read(iter, length);
            destroy_stage = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(entity_id, container);
            location.Write(container);
            WriteData<char>(destroy_stage, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
            object["location"] = location.Serialize();
            object["destroy_stage"] = picojson::value((double)destroy_stage);

            return value;
        }

    private:
        int entity_id;
        NetworkPosition location;
        char destroy_stage;

    };
} //ProtocolCraft