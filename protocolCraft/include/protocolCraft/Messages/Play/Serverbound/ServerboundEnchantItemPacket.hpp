#pragma once

#if PROTOCOL_VERSION < 476
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundEnchantItemPacket : public BaseMessage<ServerboundEnchantItemPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x06;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x07;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Enchant item";
        }

        virtual ~ServerboundEnchantItemPacket() override
        {

        }

        void SetContainerId(const char container_id_)
        {
            container_id = container_id_;
        }

        void SetEnchantment(const char enchantment_)
        {
            enchantment = enchantment_;
        }


        const char GetContainerId() const
        {
            return container_id;
        }

        const char GetEnchantment() const
        {
            return enchantment;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            container_id = ReadData<char>(iter, length);
            enchantment = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(container_id, container);
            WriteData<char>(enchantment, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["container_id"] = picojson::value((double)container_id);
            object["enchantment"] = picojson::value((double)enchantment);

            return value;
        }

    private:
        char container_id;
        char enchantment;

    };
} //ProtocolCraft
#endif
