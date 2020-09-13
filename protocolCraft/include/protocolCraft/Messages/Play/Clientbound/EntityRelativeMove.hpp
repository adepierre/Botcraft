#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class EntityRelativeMove : public BaseMessage<EntityRelativeMove>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x26;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x28;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x28;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x29;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x28;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 // 1.16.2, 1.16.3
            return 0x27;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Entity Relative Move";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetDeltaX(const short delta_x_)
        {
            delta_x = delta_x_;
        }

        void SetDeltaY(const short delta_y_)
        {
            delta_y = delta_y_;
        }

        void SetDeltaZ(const short delta_z_)
        {
            delta_z = delta_z_;
        }

        void SetOnGround(const bool on_ground_)
        {
            on_ground = on_ground_;
        }

        const int GetEntityId() const
        {
            return entity_id;
        }

        const short GetDeltaX() const
        {
            return delta_x;
        }

        const short GetDeltaY() const
        {
            return delta_y;
        }

        const short GetDeltaZ() const
        {
            return delta_z;
        }

        const bool GetOnGround() const
        {
            return on_ground;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            entity_id = ReadVarInt(iter, length);
            delta_x = ReadData<short>(iter, length);
            delta_y = ReadData<short>(iter, length);
            delta_z = ReadData<short>(iter, length);
            on_ground = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVarInt(entity_id, container);
            WriteData<short>(delta_x, container);
            WriteData<short>(delta_y, container);
            WriteData<short>(delta_z, container);
            WriteData<bool>(on_ground, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
            object["delta_x"] = picojson::value((double)delta_x);
            object["delta_y"] = picojson::value((double)delta_y);
            object["delta_z"] = picojson::value((double)delta_z);
            object["on_ground"] = picojson::value(on_ground);

            return value;
        }

    private:
        int entity_id;
        short delta_x;
        short delta_y;
        short delta_z;
        bool on_ground;
    };
} //ProtocolCraft