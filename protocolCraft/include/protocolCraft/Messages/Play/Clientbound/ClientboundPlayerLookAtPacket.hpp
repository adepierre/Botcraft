#pragma once

#if PROTOCOL_VERSION > 351
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerLookAtPacket : public BaseMessage<ClientboundPlayerLookAtPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x31;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x34;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x35;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x34;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x33;
#elif PROTOCOL_VERSION == 755 // 1.17
            return 0x37;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Face Player";
        }

        virtual ~ClientboundPlayerLookAtPacket() override
        {

        }

        void SetX(const double x_)
        {
            x = x_;
        }

        void SetY(const double y_)
        {
            y = y_;
        }

        void SetZ(const double z_)
        {
            z = z_;
        }

        void SetEntity(const int entity_)
        {
            entity = entity_;
        }

        void SetFromAnchor(const int from_anchor_)
        {
            from_anchor = from_anchor_;
        }

        void SetToAnchor(const int to_anchor_)
        {
            to_anchor = to_anchor_;
        }

        void SetAtEntity(const bool at_entity_)
        {
            at_entity = at_entity_;
        }


        const double GetX() const
        {
            return x;
        }

        const double GetY() const
        {
            return y;
        }

        const double GetZ() const
        {
            return z;
        }

        const int GetEntity() const
        {
            return entity;
        }

        const int GetFromAnchor() const
        {
            return from_anchor;
        }

        const int GetToAnchor() const
        {
            return to_anchor;
        }

        const bool GetAtEntity() const
        {
            return at_entity;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            from_anchor = ReadVarInt(iter, length);
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            at_entity = ReadData<bool>(iter, length);
            if (at_entity)
            {
                entity = ReadVarInt(iter, length);
                to_anchor = ReadVarInt(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(from_anchor, container);
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<bool>(at_entity, container);
            if (at_entity)
            {
                WriteVarInt(entity, container);
                WriteVarInt(to_anchor, container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["from_anchor"] = picojson::value((double)from_anchor);
            object["x"] = picojson::value(x);
            object["y"] = picojson::value(y);
            object["z"] = picojson::value(z);
            object["at_entity"] = picojson::value(at_entity);
            if (at_entity)
            {
                object["entity"] = picojson::value((double)entity);
                object["to_anchor"] = picojson::value((double)to_anchor);
            }

            return value;
        }

    private:
        double x;
        double y;
        double z;
        int entity;
        int from_anchor;
        int to_anchor;
        bool at_entity;

    };
} //ProtocolCraft
#endif
