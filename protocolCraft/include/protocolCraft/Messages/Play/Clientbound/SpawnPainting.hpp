#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class SpawnPainting : public BaseMessage<SpawnPainting>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x04;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x04;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x04;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x04;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x03;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 // 1.16.2, 1.16.3
            return 0x03;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Spawn Painting";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetEntityUuid(const UUID& entity_uuid_)
        {
            entity_uuid = entity_uuid_;
        }

#if PROTOCOL_VERSION < 353
        void SetTitle(const std::string title_)
        {
            title = title_;
        }
#else
        void SetMotive(const int motive_)
        {
            motive = motive_;
        }
#endif

        void SetLocation(const NetworkPosition location_)
        {
            location = location_;
        }

        void SetDirection(const char direction_)
        {
            direction = direction_;
        }


        const int GetEntityId() const
        {
            return entity_id;
        }

        const UUID& GetEntityUuid() const
        {
            return entity_uuid;
        }

#if PROTOCOL_VERSION < 353
        const std::string GetTitle() const
        {
            return title;
        }
#else
        const int GetMotive() const
        {
            return motive;
        }
#endif
        const NetworkPosition GetLocation() const
        {
            return location;
        }

        const char GetDirection() const
        {
            return direction;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadVarInt(iter, length);
            entity_uuid = ReadUUID(iter, length);
#if PROTOCOL_VERSION < 353
            title = ReadString(iter, length);
#else
            motive = ReadVarInt(iter, length);
#endif
            location.Read(iter, length);
            direction = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(entity_id, container);
            WriteUUID(entity_uuid, container);
#if PROTOCOL_VERSION < 353
            WriteString(title, container);
#else
            WriteVarInt(motive, container);
#endif
            location.Write(container);
            WriteData<char>(direction, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
            object["entity_uuid"] = picojson::value(entity_uuid);
#if PROTOCOL_VERSION < 353
            object["title"] = picojson::value(title);
#else
            object["motive"] = picojson::value((double)motive);
#endif
            object["location"] = location.Serialize();
            object["direction"] = picojson::value((double)direction);

            return value;
        }

    private:
        int entity_id;
        UUID entity_uuid;
#if PROTOCOL_VERSION < 353
        std::string title;
#else
        int motive;
#endif
        NetworkPosition location;
        char direction;

    };
} //ProtocolCraft