#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class UpdateBlockEntity : public BaseMessage<UpdateBlockEntity>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x09;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x09;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x09;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x0A;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
            return 0x09;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update Block Entity";
        }

        void SetLocation(const NetworkPosition& location_)
        {
            location = location_;
        }

        void SetAction(const unsigned char action_)
        {
            action = action_;
        }

        void SetNBTData(const NBT& nbt_data_)
        {
            nbt_data = nbt_data_;
        }

        const NetworkPosition& GetLocation() const
        {
            return location;
        }

        const unsigned char GetAction() const
        {
            return action;
        }

        const NBT& GetNBTData() const
        {
            return nbt_data;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            location.Read(iter, length);
            action = ReadData<unsigned char>(iter, length);
            nbt_data.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            location.Write(container);
            WriteData<unsigned char>(action, container);
            nbt_data.Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["location"] = location.Serialize();
            object["action"] = picojson::value((double)action);
            object["nbt_data"] = nbt_data.Serialize();

            return value;
        }

    private:
        NetworkPosition location;
        unsigned char action;
        NBT nbt_data;
    };
} //ProtocolCraft