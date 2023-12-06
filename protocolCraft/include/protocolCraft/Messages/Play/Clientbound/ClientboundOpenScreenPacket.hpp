#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundOpenScreenPacket : public BaseMessage<ClientboundOpenScreenPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x2F;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x2D;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x2D;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x2C;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x30;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3 */
        static constexpr int packet_id = 0x31;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Open Screen";

        virtual ~ClientboundOpenScreenPacket() override
        {

        }

#if PROTOCOL_VERSION < 452 /* < 1.14 */
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

#if PROTOCOL_VERSION < 452 /* < 1.14 */
        void SetNumberOfSlots(const unsigned char number_of_slots_)
        {
            number_of_slots = number_of_slots_;
        }

        void SetId_(const int id__)
        {
            id_ = id__;
        }
#endif

#if PROTOCOL_VERSION < 452 /* < 1.14 */
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

#if PROTOCOL_VERSION < 452 /* < 1.14 */
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
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 452 /* < 1.14 */
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

        virtual void WriteImpl(WriteContainer& container) const override
        {            
#if PROTOCOL_VERSION < 452 /* < 1.14 */
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

#if PROTOCOL_VERSION < 452 /* < 1.14 */
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
#if PROTOCOL_VERSION < 452 /* < 1.14 */
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
