#pragma once

#if PROTOCOL_VERSION < 476
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class EnchantItem : public BaseMessage<EnchantItem>
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

        void SetWindowId(const char window_id_)
        {
            window_id = window_id_;
        }

        void SetEnchantment(const char enchantment_)
        {
            enchantment = enchantment_;
        }


        const char GetWindowId() const
        {
            return window_id;
        }

        const char GetEnchantment() const
        {
            return enchantment;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            window_id = ReadData<char>(iter, length);
            enchantment = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(window_id, container);
            WriteData<char>(enchantment, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["window_id"] = picojson::value((double)window_id);
            object["enchantment"] = picojson::value((double)enchantment);

            return value;
        }

    private:
        char window_id;
        char enchantment;

    };
} //ProtocolCraft
#endif
