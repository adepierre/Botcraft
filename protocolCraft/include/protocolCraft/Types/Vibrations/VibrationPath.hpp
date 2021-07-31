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
            origin.Read(iter, length);
            destination_type.Read(iter, length);
            destination = PositionSource::CreatePositionSource(destination_type);
            destination->Read(iter, length);
            arrival_in_ticks = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            origin.Write(container);
            destination_type.Write(container);
            destination->Write(container);
            WriteData<VarInt>(arrival_in_ticks, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["origin"] = origin.Serialize();
            object["destination"] = destination->Serialize();
            object["arrival_in_ticks"] = picojson::value((double)arrival_in_ticks);


            return value;
        }

    private:
        NetworkPosition origin;
        Identifier destination_type;
        std::shared_ptr<PositionSource> destination;
        int arrival_in_ticks;
    };
} // ProtocolCraft
#endif