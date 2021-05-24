#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerSetContentPacket : public BaseMessage<ClientboundContainerSetContentPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x14;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x15;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x14;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x15;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x14;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x13;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Container Set Content";
        }

        virtual ~ClientboundContainerSetContentPacket() override
        {

        }

        void SetContainerId(const unsigned char container_id_)
        {
            container_id = container_id_;
        }

        void SetItems(const std::vector<Slot>& items_)
        {
            items = items_;
        }

        const unsigned char GetContainerId() const
        {
            return container_id;
        }

        const std::vector<Slot>& GetSlotData() const
        {
            return items;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            container_id = ReadData<unsigned char>(iter, length);
            short count = ReadData<short>(iter, length);
            items = std::vector<Slot>(count);
            for (int i = 0; i < count; ++i)
            {
                items[i].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<unsigned char>(container_id, container);
            WriteData<short>(items.size(), container);
            for (int i = 0; i < items.size(); ++i)
            {
                items[i].Write(container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["container_id"] = picojson::value((double)container_id);
            object["items"] = picojson::value(picojson::array_type, false);

            picojson::array& array = object["items"].get<picojson::array>();
            array.reserve(items.size());

            for (int i = 0; i < items.size(); ++i)
            {
                array.push_back(items[i].Serialize());
            }

            return value;
        }

    private:
        unsigned char container_id;
        std::vector<Slot> items;
    };
} //ProtocolCraft