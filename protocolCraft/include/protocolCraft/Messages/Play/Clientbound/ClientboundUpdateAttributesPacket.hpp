#pragma once

#include <vector>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/EntityProperty.hpp"

namespace ProtocolCraft
{
    class ClientboundUpdateAttributesPacket : public BaseMessage<ClientboundUpdateAttributesPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x4E;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x52;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x58;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x59;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x58;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x58;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x63;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x64;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x65;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x68;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x66;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Update Attributes";

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


        int GetEntityId() const
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
            attributes = ReadVector<EntityProperty, int>(iter, length);
#else
            attributes = ReadVector<EntityProperty>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(entity_id, container);
#if PROTOCOL_VERSION < 755
            WriteVector<EntityProperty, int>(attributes, container);
#else
            WriteVector<EntityProperty>(attributes, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["entity_id"] = entity_id;
            
            output["attributes"] = nlohmann::json::array();
            for (const auto& a : attributes)
            {
                output["attributes"].push_back(a.Serialize());
            }

            return output;
        }

    private:
        int entity_id;
        std::vector<EntityProperty> attributes;

    };
} //ProtocolCraft
