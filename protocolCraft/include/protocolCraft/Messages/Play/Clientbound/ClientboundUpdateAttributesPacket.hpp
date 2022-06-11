#pragma once

#include <vector>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/EntityProperty.hpp"

namespace ProtocolCraft
{
    class ClientboundUpdateAttributesPacket : public BaseMessage<ClientboundUpdateAttributesPacket>
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
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x63;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x64;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x65;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update Attributes";
        }

        virtual ~ClientboundUpdateAttributesPacket() override
        {

        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetAttributes(const std::vector<EntityProperty>& attributes_)
        {
            attributes = attributes_;
        }


        const int GetEntityId() const
        {
            return entity_id;
        }

        const std::vector<EntityProperty>& GetAttributes() const
        {
            return attributes;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadData<VarInt>(iter, length);

#if PROTOCOL_VERSION < 755
            const int attributes_size = ReadData<int>(iter, length);
#else
            const int attributes_size = ReadData<VarInt>(iter, length);
#endif
            attributes = std::vector<EntityProperty>(attributes_size);
            for (int i = 0; i < attributes_size; ++i)
            {
                attributes[i].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(entity_id, container);
#if PROTOCOL_VERSION < 755
            WriteData<int>(attributes.size(), container);
#else
            WriteData<VarInt>(attributes.size(), container);
#endif
            for (int i = 0; i < attributes.size(); ++i)
            {
                attributes[i].Write(container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["entity_id"] = entity_id;
            
            output["attributes"] = nlohmann::json::array();
            for (int i = 0; i < attributes.size(); ++i)
            {
                output["attributes"].push_back(attributes[i].Serialize());
            }

            return output;
        }

    private:
        int entity_id;
        std::vector<EntityProperty> attributes;

    };
} //ProtocolCraft