#pragma once

#if PROTOCOL_VERSION > 754
#include <memory>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"
#include "protocolCraft/Types/Vibrations/PositionSource.hpp"

namespace ProtocolCraft 
{
    class VibrationPath : public NetworkType
    {
    public:
        virtual ~VibrationPath() override
        {

        }


        void SetOrigin(const NetworkPosition& origin_)
        {
            origin = origin_;
        }

        void SetDestinationType(const Identifier& destination_type_)
        {
            destination_type = destination_type_;
        }

        void SetDestination(const std::shared_ptr<PositionSource> destination_)
        {
            destination = destination_;
        }

        void SetArrivalInTicks(const int arrival_in_ticks_)
        {
            arrival_in_ticks = arrival_in_ticks_;
        }


        const NetworkPosition& GetOrigin() const
        {
            return origin;
        }

        const Identifier& GetDestinationType() const
        {
            return destination_type;
        }

        const std::shared_ptr<PositionSource> GetDestination() const
        {
            return destination;
        }

        const int GetArrivalInTicks() const
        {
            return arrival_in_ticks;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            origin = ReadData<NetworkPosition>(iter, length);
            destination_type = ReadData<Identifier>(iter, length);
            destination = PositionSource::CreatePositionSource(destination_type);
            destination->Read(iter, length);
            arrival_in_ticks = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<NetworkPosition>(origin, container);
            WriteData<Identifier>(destination_type, container);
            destination->Write(container);
            WriteData<VarInt>(arrival_in_ticks, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["origin"] = origin.Serialize();
            output["destination"] = destination->Serialize();
            output["arrival_in_ticks"] = arrival_in_ticks;


            return output;
        }

    private:
        NetworkPosition origin;
        Identifier destination_type;
        std::shared_ptr<PositionSource> destination;
        int arrival_in_ticks;
    };
} // ProtocolCraft
#endif
