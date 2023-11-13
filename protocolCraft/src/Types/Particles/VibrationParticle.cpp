#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Types/Particles/VibrationParticle.hpp"

namespace ProtocolCraft
{
    VibrationParticle::VibrationParticle()
    {
        
    }
    
    VibrationParticle::~VibrationParticle()
    {
        
    }
    
    std::string VibrationParticle::GetName() const
    {
        return "vibration";
    }
    
    ParticleType VibrationParticle::GetType() const
    {
        return ParticleType::Vibration;
    }

#if PROTOCOL_VERSION < 759 /* < 1.19 */
    const VibrationPath& VibrationParticle::GetVibrationPath() const
    {
        return vibration_path;
    }
#else
    const std::shared_ptr<PositionSource>& VibrationParticle::GetDestination() const
    {
        return destination;
    }

    const Identifier& VibrationParticle::GetDestinationType() const
    {
        return destination_type;
    }

    int VibrationParticle::GetArrivalInTicks() const
    {
        return arrival_in_ticks;
    }
#endif

#if PROTOCOL_VERSION < 759 /* < 1.19 */
    void VibrationParticle::SetVibrationPath(const VibrationPath& vibration_path_)
    {
        vibration_path = vibration_path_;
    }
#else
    void VibrationParticle::SetDestinationType(const Identifier& destination_type_)
    {
        destination_type = destination_type_;
    }

    void VibrationParticle::SetDestination(const std::shared_ptr<PositionSource>& destination_)
    {
        destination = destination_;
    }

    void VibrationParticle::SetArrivalInTicks(const int arrival_in_ticks_)
    {
        arrival_in_ticks = arrival_in_ticks_;
    }
#endif
    
    void VibrationParticle::ReadImpl(ReadIterator& iter, size_t& length)
    {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        vibration_path = ReadData<VibrationPath>(iter, length);
#else
        destination_type = ReadData<Identifier>(iter, length);
        destination = PositionSource::CreatePositionSource(destination_type);
        destination->Read(iter, length);
        arrival_in_ticks = ReadData<VarInt>(iter, length);
#endif
    }
    
    void VibrationParticle::WriteImpl(WriteContainer& container) const
    {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        WriteData<VibrationPath>(vibration_path, container);
#else
        WriteData<Identifier>(destination_type, container);
        destination->Write(container);
        WriteData<VarInt>(arrival_in_ticks, container);
#endif
    }
    
    Json::Value VibrationParticle::SerializeImpl() const
    {
        Json::Value output;

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        output["vibration_path"] = vibration_path;
#else
        output["destination_type"] = destination_type;
        output["destination"] = destination->Serialize();
        output["arrival_in_ticks"] = arrival_in_ticks;
#endif
        return output;
    }
}
#endif
