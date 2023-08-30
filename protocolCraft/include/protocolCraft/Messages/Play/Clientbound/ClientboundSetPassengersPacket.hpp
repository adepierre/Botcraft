#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetPassengersPacket : public BaseMessage<ClientboundSetPassengersPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x43;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x46;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x4A;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578 || PROTOCOL_VERSION == 735 ||  \
      PROTOCOL_VERSION == 736 || PROTOCOL_VERSION == 751 ||  \
      PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x4B;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 ||  \
      PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x54;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x57;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x55;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x59;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Passengers";

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


        int GetVehicle() const
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
            passengers = ReadVector<int>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadData<VarInt>(i, l);
                }
            );
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(vehicle, container);
            WriteVector<int>(passengers, container,
                [](const int& i, WriteContainer& c)
                {
                    WriteData<VarInt>(i, c);
                }
            );
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["vehicle"] = vehicle;
            output["passengers"] = passengers;

            return output;
        }

    private:
        int vehicle = 0;
        std::vector<int> passengers;

    };
} //ProtocolCraft
