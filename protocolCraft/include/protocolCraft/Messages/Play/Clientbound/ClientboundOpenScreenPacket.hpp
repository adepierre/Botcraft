#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundOpenScreenPacket : public BaseMessage<ClientboundOpenScreenPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x2F;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x2D;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x2D;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x2C;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x30;
#elif PROTOCOL_VERSION == 763 // 1.20
        static constexpr int packet_id = 0x30;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Open Screen";

        virtual ~ClientboundOpenScreenPacket() override
        {

        }

#if PROTOCOL_VERSION < 452
        void SetContainerId(const unsigned char container_id_)
        {
            container_id = container_id_;
        }

        void SetType(const std::string& type_)
        {
            type = type_;
        }
#else
        void SetContainerId(const int container_id_)
        {
            container_id = container_id_;
        }

        void SetType(const int type_)
        {
            type = type_;
        }
#endif

        void SetTitle(const Chat& title_)
        {
            title = title_;
        }

#if PROTOCOL_VERSION < 452
        void SetNumberOfSlots(const unsigned char number_of_slots_)
        {
            number_of_slots = number_of_slots_;
        }

        void SetId_(const int id__)
        {
            id_ = id__;
        }
#endif

#if PROTOCOL_VERSION < 452
        unsigned char GetContainerId() const
        {
            return container_id;
        }

        const std::string& GetType() const
        {
            return type;
        }
#else
        int GetContainerId() const
        {
            return container_id;
        }

        int GetType() const
        {
            return type;
        }
#endif

        const Chat& GetTitle() const
        {
            return title;
        }

#if PROTOCOL_VERSION < 452
        unsigned char GetNumberOfSlots() const
        {
            return number_of_slots;
        }

        int GetId_() const
        {
            return id_;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
#if PROTOCOL_VERSION < 452
            container_id = ReadData<unsigned char>(iter, length);
            type = ReadData<std::string>(iter, length);
            title = ReadData<Chat>(iter, length);
            number_of_slots = ReadData<unsigned char>(iter, length);
            if (type == "EntityHorse")
            {
                id_ = ReadData<int>(iter, length);
            }
#else
            container_id = ReadData<VarInt>(iter, length);
            type = ReadData<VarInt>(iter, length);
            title = ReadData<Chat>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {            
#if PROTOCOL_VERSION < 452
            WriteData<unsigned char>(container_id, container);
            WriteData<std::string>(type, container);
            WriteData<Chat>(title, container);
            WriteData<unsigned char>(number_of_slots, container);
            if (type == "EntityHorse")
            {
                WriteData<int>(id_, container);
            }
#else
            WriteData<VarInt>(container_id, container);
            WriteData<VarInt>(type, container);
            WriteData<Chat>(title, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 452
            output["container_id"] = container_id;
            output["type"] = type;
            output["number_of_slots"] = number_of_slots;
            output["id_"] = id_;
#else
            output["container_id"] = container_id;
            output["type"] = type;
#endif

            output["title"] = title;

            return output;
        }

    private:
#if PROTOCOL_VERSION < 452
        unsigned char container_id = 0;
        std::string type;
        unsigned char number_of_slots = 0;
        int id_ = 0;
#else
        int container_id = 0;
        int type = 0;
#endif
        Chat title;
    };
} //ProtocolCraft
