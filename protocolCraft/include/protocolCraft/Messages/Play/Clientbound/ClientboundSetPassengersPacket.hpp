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
            vehicle = ReadData<VarInt>(iter, length);
            int passengers_count = ReadData<VarInt>(iter, length);
            passengers = std::vector<int>(passengers_count);
            for (int i = 0; i < passengers_count; ++i)
            {
                passengers[i] = ReadData<VarInt>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(vehicle, container);
            WriteData<VarInt>(passengers.size(), container);
            for (int i = 0; i < passengers.size(); ++i)
            {
                WriteData<VarInt>(passengers[i], container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["vehicle"] = vehicle;
            output["passengers"] = passengers;

            return output;
        }

    private:
        int vehicle;
        std::vector<int> passengers;

    };
} //ProtocolCraft