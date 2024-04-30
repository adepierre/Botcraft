#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Types/Particles/VibrationParticleOptions.hpp"

namespace ProtocolCraft
{
    VibrationParticleOptions::VibrationParticleOptions()
    {
        
    }
    
    VibrationParticleOptions::~VibrationParticleOptions()
    {
        
    }

#if PROTOCOL_VERSION < 759 /* < 1.19 */
    const VibrationPath& VibrationParticleOptions::GetVibrationPath() const
    {
        return vibration_path;
    }
#else
    const std::shared_ptr<PositionSource>& VibrationParticleOptions::GetDestination() const
    {
        return destination;
    }

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    PositionSourceType VibrationParticleOptions::GetDestinationType() const
    {
        return destination_type;
    }
#else
    const Identifier& VibrationParticleOptions::GetDestinationType() const
    {
        return destination_type;
    }
#endif

    int VibrationParticleOptions::GetArrivalInTicks() const
    {
        return arrival_in_ticks;
    }
#endif

#if PROTOCOL_VERSION < 759 /* < 1.19 */
    void VibrationParticleOptions::SetVibrationPath(const VibrationPath& vibration_path_)
    {
        vibration_path = vibration_path_;
    }
#else
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    void VibrationParticleOptions::SetDestinationType(const PositionSourceType destination_type_)
    {
        destination_type = destination_type_;
    }
#else
    void VibrationParticleOptions::SetDestinationType(const Identifier& destination_type_)
    {
        destination_type = destination_type_;
    }
#endif

    void VibrationParticleOptions::SetDestination(const std::shared_ptr<PositionSource>& destination_)
    {
        destination = destination_;
    }

    void VibrationParticleOptions::SetArrivalInTicks(const int arrival_in_ticks_)
    {
        arrival_in_ticks = arrival_in_ticks_;
    }
#endif
    
    void VibrationParticleOptions::ReadImpl(ReadIterator& iter, size_t& length)
    {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        vibration_path = ReadData<VibrationPath>(iter, length);
#else
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        destination_type = static_cast<PositionSourceType>(static_cast<int>(ReadData<VarInt>(iter, length)));
#else
        destination_type = ReadData<Identifier>(iter, length);
#endif
        destination = PositionSource::CreatePositionSource(destination_type);
        destination->Read(iter, length);
        arrival_in_ticks = ReadData<VarInt>(iter, length);
#endif
    }
    
    void VibrationParticleOptions::WriteImpl(WriteContainer& container) const
    {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        WriteData<VibrationPath>(vibration_path, container);
#else
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        WriteData<VarInt>(static_cast<int>(destination_type), container);
#else
        WriteData<Identifier>(destination_type, container);
#endif
        destination->Write(container);
        WriteData<VarInt>(arrival_in_ticks, container);
#endif
    }
    
    Json::Value VibrationParticleOptions::SerializeImpl() const
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
