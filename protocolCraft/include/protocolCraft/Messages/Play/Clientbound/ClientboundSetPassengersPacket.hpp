#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetPassengersPacket : public BaseMessage<ClientboundSetPassengersPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x43;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x46;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x4A;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x4B;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x4B;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x4B;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x54;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Passengers";
        }

        virtual ~ClientboundSetPassengersPacket() override
        {

        }

        void SetVehicle(const int vehicle_)
        {
            vehicle = vehicle_;
        }

        void SetPassengers(const std::vector<int>& passengers_)
        {
            passengers = passengers_;
        }


        const int GetVehicle() const
        {
            return vehicle;
        }

        const std::vector<int>& GetPassengers() const
        {
            return passengers;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            vehicle = ReadVarInt(iter, length);
            int passengers_count = ReadVarInt(iter, length);
            passengers = std::vector<int>(passengers_count);
            for (int i = 0; i < passengers_count; ++i)
            {
                passengers[i] = ReadVarInt(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(vehicle, container);
            WriteVarInt(passengers.size(), container);
            for (int i = 0; i < passengers.size(); ++i)
            {
                WriteVarInt(passengers[i], container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["vehicle"] = picojson::value((double)vehicle);
            object["passengers"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["passengers"].get<picojson::array>();

            for (int i = 0; i < passengers.size(); ++i)
            {
                array.push_back(picojson::value((double)passengers[i]));
            }

            return value;
        }

    private:
        int vehicle;
        std::vector<int> passengers;

    };
} //ProtocolCraft