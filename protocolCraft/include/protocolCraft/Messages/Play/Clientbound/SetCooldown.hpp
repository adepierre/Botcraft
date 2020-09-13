#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class SetCooldown : public BaseMessage<SetCooldown>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x17;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x18;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x17;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x18;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x17;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 // 1.16.2, 1.16.3
            return 0x16;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Cooldown";
        }

        void SetItemId(const int item_id_)
        {
            item_id = item_id_;
        }

        void SetCooldownTicks(const int cooldown_ticks_)
        {
            cooldown_ticks = cooldown_ticks_;
        }


        const int GetItemId() const
        {
            return item_id;
        }

        const int GetCooldownTicks() const
        {
            return cooldown_ticks;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            item_id = ReadVarInt(iter, length);
            cooldown_ticks = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(item_id, container);
            WriteVarInt(cooldown_ticks, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["item_id"] = picojson::value((double)item_id);
            object["cooldown_ticks"] = picojson::value((double)cooldown_ticks);

            return value;
        }

    private:
        int item_id;
        int cooldown_ticks;

    };
} //ProtocolCraft