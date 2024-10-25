#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include <memory>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"
#include "protocolCraft/Types/Vibrations/PositionSource.hpp"

namespace ProtocolCraft
{
    class VibrationPath : public NetworkType
    {
        SERIALIZED_FIELD(Origin, NetworkPosition);
        SERIALIZED_FIELD(DestinationType, Identifier);
        SERIALIZED_FIELD(Destination, std::shared_ptr<PositionSource>);
        SERIALIZED_FIELD(ArrivalInTicks, VarInt);

        DEFINE_UTILITIES;
    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetOrigin(ReadData<NetworkPosition>(iter, length));
            SetDestinationType(ReadData<Identifier>(iter, length));
            std::shared_ptr<PositionSource> destination = PositionSource::CreatePositionSource(GetDestinationType());
            destination->Read(iter, length);
            SetDestination(destination);
            SetArrivalInTicks(ReadData<VarInt>(iter, length));
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<NetworkPosition>(GetOrigin(), container);
            WriteData<Identifier>(GetDestinationType(), container);
            GetDestination()->Write(container);
            WriteData<VarInt>(GetArrivalInTicks(), container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(field_name<Origin_index>)] = GetOrigin();
            output[std::string(field_name<DestinationType_index>)] = GetDestinationType();
            output[std::string(field_name<Destination_index>)] = *GetDestination();
            output[std::string(field_name<ArrivalInTicks_index>)] = GetArrivalInTicks();

            return output;
        }
    };
} // ProtocolCraft
#endif
