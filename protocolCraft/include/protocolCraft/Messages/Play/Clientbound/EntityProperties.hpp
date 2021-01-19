#pragma once

#include <vector>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/EntityProperty.hpp"

namespace ProtocolCraft
{
    class EntityProperties : public BaseMessage<EntityProperties>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x4E;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x52;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x58;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x59;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x58;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x58;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Entity Properties";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetNumberOfProperties(const int number_of_properties_)
        {
            number_of_properties = number_of_properties_;
        }

        void SetProperty(const std::vector<EntityProperty>& property_)
        {
            property = property_;
        }


        const int GetEntityId() const
        {
            return entity_id;
        }

        const int GetNumberOfProperties() const
        {
            return number_of_properties;
        }

        const std::vector<EntityProperty>& GetProperty() const
        {
            return property;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadVarInt(iter, length);
            number_of_properties = ReadData<int>(iter, length);
            property = std::vector<EntityProperty>(number_of_properties);
            for (int i = 0; i < number_of_properties; ++i)
            {
                property[i].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(entity_id, container);
            WriteData<int>(number_of_properties, container);
            for (int i = 0; i < number_of_properties; ++i)
            {
                property[i].Write(container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
            object["number_of_properties"] = picojson::value((double)number_of_properties);

            object["property"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["property"].get<picojson::array>();
            for (int i = 0; i < number_of_properties; ++i)
            {
                array.push_back(property[i].Serialize());
            }

            return value;
        }

    private:
        int entity_id;
        int number_of_properties;
        std::vector<EntityProperty> property;

    };
} //ProtocolCraft