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
        DECLARE_FIELDS_TYPES(NetworkPosition, Identifier,      std::shared_ptr<PositionSource>, VarInt);
        DECLARE_FIELDS_NAMES(Origin,          DestinationType, Destination,                     ArrivalInTicks);

        GETTER_SETTER(Origin);
        GETTER_SETTER(DestinationType);
        GETTER_SETTER(Destination);
        GETTER_SETTER(ArrivalInTicks);
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

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Origin)])] = GetOrigin();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::DestinationType)])] = GetDestinationType();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Destination)])] = *GetDestination();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::ArrivalInTicks)])] = GetArrivalInTicks();


            return output;
        }
    };
} // ProtocolCraft
#endif
