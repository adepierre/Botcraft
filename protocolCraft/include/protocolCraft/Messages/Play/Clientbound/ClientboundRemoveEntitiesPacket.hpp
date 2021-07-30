#pragma once

#if PROTOCOL_VERSION < 755 || PROTOCOL_VERSION > 755
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundRemoveEntitiesPacket : public BaseMessage<ClientboundRemoveEntitiesPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x32;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x35;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x37;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x38;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x37;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x36;
#elif PROTOCOL_VERSION == 756 // 1.17.1
            return 0x3A;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Remove Entities";
        }

        virtual ~ClientboundRemoveEntitiesPacket() override
        {

        }


        void SetEntityIds(const std::vector<int>& entity_ids_)
        {
            entity_ids = entity_ids_;
        }


        const std::vector<int>& GetEntityIds() const
        {
            return entity_ids;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            const int entity_ids_size = ReadVarInt(iter, length);
            entity_ids = std::vector<int>(entity_ids_size);
            for (int i = 0; i < entity_ids_size; ++i)
            {
                entity_ids[i] = ReadVarInt(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(entity_ids.size(), container);
            for (int i = 0; i < entity_ids.size(); ++i)
            {
                WriteVarInt(entity_ids[i], container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_ids"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["entity_ids"].get<picojson::array>();
            for (int i = 0; i < entity_ids.size(); ++i)
            {
                array.push_back(picojson::value((double)entity_ids[i]));
            }

            return value;
        }

    private:
        std::vector<int> entity_ids;

    };
} //ProtocolCraft
#endif