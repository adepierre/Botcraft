#pragma once

#if PROTOCOL_VERSION > 451
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundHorseScreenOpenPacket : public BaseMessage<ClientboundHorseScreenOpenPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1F;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x20;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x1F;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x1E;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x1F;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Horse Screen Open";
        }

        virtual ~ClientboundHorseScreenOpenPacket() override
        {

        }

        void SetContainerId(const char container_id_)
        {
            container_id = container_id_;
        }

        void SetSize(const int size_)
        {
            size = size_;
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }


        const char GetContainerId() const
        {
            return container_id;
        }

        const int GetSize() const
        {
            return size;
        }

        const int GetEntityId() const
        {
            return entity_id;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            container_id = ReadData<char>(iter, length);
            size = ReadVarInt(iter, length);
            entity_id = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(container_id, container);
            WriteVarInt(size, container);
            WriteData<int>(entity_id, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["container_id"] = picojson::value((double)container_id);
            object["size"] = picojson::value((double)size);
            object["entity_id"] = picojson::value((double)entity_id);

            return value;
        }

    private:
        char container_id;
        int size;
        int entity_id;

    };
} //ProtocolCraft
#endif
