#pragma once

#if PROTOCOL_VERSION > 450
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class OpenBook : public BaseMessage<OpenBook>
    {
    public:
        virtual const int GetId() const override
        {

#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x2D;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x2E;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x2D;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4
            return 0x2C;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Open Book";
        }

        void SetHand(const int hand_)
        {
            hand = hand_;
        }


        const int GetHand() const
        {
            return hand;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            hand = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(hand, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["hand"] = picojson::value((double)hand);

            return value;
        }

    private:
        int hand;

    };
} //ProtocolCraft
#endif
