#pragma once

#if PROTOCOL_VERSION > 385
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class SetBeaconEffect : public BaseMessage<SetBeaconEffect>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x20;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x22;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x22;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x23;
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x24;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Beacon Effect";
        }

        void SetPrimaryEffect(const int primary_effect_)
        {
            primary_effect = primary_effect_;
        }

        void SetSecondaryEffect(const int secondary_effect_)
        {
            secondary_effect = secondary_effect_;
        }


        const int GetPrimaryEffect() const
        {
            return primary_effect;
        }

        const int GetSecondaryEffect() const
        {
            return secondary_effect;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            primary_effect = ReadVarInt(iter, length);
            secondary_effect = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(primary_effect, container);
            WriteVarInt(secondary_effect, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["primary_effect"] = picojson::value((double)primary_effect);
            object["secondary_effect"] = picojson::value((double)secondary_effect);

            return value;
        }

    private:
        int primary_effect;
        int secondary_effect;

    };
} //ProtocolCraft
#endif
