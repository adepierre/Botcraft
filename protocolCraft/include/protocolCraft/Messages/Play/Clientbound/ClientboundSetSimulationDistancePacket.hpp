#pragma once

#if PROTOCOL_VERSION > 756
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetSimulationDistancePacket : public BaseMessage<ClientboundSetSimulationDistancePacket>
    {
    public:
#if PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x57;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x57;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x5A;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x58;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Set Simulation Distance";

        virtual ~ClientboundSetSimulationDistancePacket() override
        {

        }

        void SetSimulationDistance(const int simulation_distance_)
        {
            simulation_distance = simulation_distance_;
        }


        int GetSimulationDistance() const
        {
            return simulation_distance;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            simulation_distance = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(simulation_distance, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["simulation_distance"] = simulation_distance;

            return output;
        }

    private:
        int simulation_distance;

    };
} //ProtocolCraft
#endif
