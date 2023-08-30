#pragma once

#if PROTOCOL_VERSION < 476
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundEnchantItemPacket : public BaseMessage<ServerboundEnchantItemPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x06;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x07;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Enchant item";

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


        char GetContainerId() const
        {
            return container_id;
        }

        char GetEnchantment() const
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

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["container_id"] = container_id;
            output["enchantment"] = enchantment;

            return output;
        }

    private:
        char container_id = 0;
        char enchantment = 0;

    };
} //ProtocolCraft
#endif
