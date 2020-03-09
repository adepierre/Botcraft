#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class PlayerDigging : public BaseMessage<PlayerDigging>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x14;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x18;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1A;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x1A;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Digging";
        }

        void SetStatus(const int status_)
        {
            status = status_;
        }

        void SetLocation(const NetworkPosition &pos)
        {
            location = pos;
        }

        void SetFace(const int f)
        {
            face = f;
        }

        const int GetStatus() const
        {
            return status;
        }

        const NetworkPosition GetLocation() const
        {
            return location;
        }

        const int GetFace() const
        {
            return face;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            status = ReadVarInt(iter, length);
            location.Read(iter, length);
            face = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVarInt(status, container);
            location.Write(container);
            WriteData<char>(face, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["status"] = picojson::value((double)status);
            object["location"] = location.Serialize();
            object["face"] = picojson::value((double)face);

            return value;
        }

    private:
        int status;
        NetworkPosition location;
        char face;
    };
} //ProtocolCraft