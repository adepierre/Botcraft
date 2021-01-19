#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class RemoveEntityEffect : public BaseMessage<RemoveEntityEffect>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x33;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x36;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x38;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x39;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x38;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x37;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Remove Entity Effect";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetEffectId(const char effect_id_)
        {
            effect_id = effect_id_;
        }


        const int GetEntityId() const
        {
            return entity_id;
        }

        const char GetEffectId() const
        {
            return effect_id;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadVarInt(iter, length);
            effect_id = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(entity_id, container);
            WriteData<char>(effect_id, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
            object["effect_id"] = picojson::value((double)effect_id);

            return value;
        }

    private:
        int entity_id;
        char effect_id;

    };
} //ProtocolCraft