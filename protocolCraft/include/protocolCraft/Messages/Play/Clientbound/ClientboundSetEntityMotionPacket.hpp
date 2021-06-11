#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEntityMotionPacket : public BaseMessage<ClientboundSetEntityMotionPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x3E;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x41;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x45;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x46;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x46;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x46;
#elif PROTOCOL_VERSION == 755 // 1.17
            return 0x4F;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Entity Motion";
        }

        virtual ~ClientboundSetEntityMotionPacket() override
        {

        }

        void SetId_(const int id__)
        {
            id_ = id__;
        }

        void SetXA(const short x_a_)
        {
            x_a = x_a_;
        }

        void SetYA(const short y_a_)
        {
            y_a = y_a_;
        }

        void SetZA(const short z_a_)
        {
            z_a = z_a_;
        }


        const int GetId_() const
        {
            return id_;
        }

        const short GetXA() const
        {
            return x_a;
        }

        const short GetYA() const
        {
            return y_a;
        }

        const short GetZA() const
        {
            return z_a;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadVarInt(iter, length);
            x_a = ReadData<short>(iter, length);
            y_a = ReadData<short>(iter, length);
            z_a = ReadData<short>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(id_, container);
            WriteData<short>(x_a, container);
            WriteData<short>(y_a, container);
            WriteData<short>(z_a, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["id_"] = picojson::value((double)id_);
            object["x_a"] = picojson::value((double)x_a);
            object["y_a"] = picojson::value((double)y_a);
            object["z_a"] = picojson::value((double)z_a);

            return value;
        }

    private:
        int id_;
        short x_a;
        short y_a;
        short z_a;

    };
} //ProtocolCraft