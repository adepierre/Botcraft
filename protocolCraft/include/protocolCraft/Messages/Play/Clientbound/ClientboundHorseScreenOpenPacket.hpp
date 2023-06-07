#pragma once

#if PROTOCOL_VERSION > 451
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundHorseScreenOpenPacket : public BaseMessage<ClientboundHorseScreenOpenPacket>
    {
    public:
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 763 // 1.20
        static constexpr int packet_id = 0x20;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Horse Screen Open";

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


        char GetContainerId() const
        {
            return container_id;
        }

        int GetSize() const
        {
            return size;
        }

        int GetEntityId() const
        {
            return entity_id;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            container_id = ReadData<char>(iter, length);
            size = ReadData<VarInt>(iter, length);
            entity_id = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(container_id, container);
            WriteData<VarInt>(size, container);
            WriteData<int>(entity_id, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["container_id"] = container_id;
            output["size"] = size;
            output["entity_id"] = entity_id;

            return output;
        }

    private:
        char container_id;
        int size;
        int entity_id;

    };
} //ProtocolCraft
#endif
