#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOption.hpp"

#if PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Types/Vibrations/VibrationPath.hpp"
#else
#include "protocolCraft/Types/Vibrations/PositionSource.hpp"
#endif

namespace ProtocolCraft
{
    class VibrationParticleOption : public ParticleOption
    {
    public:
        VibrationParticleOption() {}
        virtual ~VibrationParticleOption() override {}

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        const VibrationPath& GetVibrationPath() const
        {
            return vibration_path;
        }
#else
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        PositionSourceType GetDestinationType() const
        {
            return destination_type;
        }
#else
        const Identifier& GetDestinationType() const
        {
            return destination_type;
        }
#endif
        const std::shared_ptr<PositionSource>& GetDestination() const
        {
            return destination;
        }

        int GetArrivalInTicks() const
        {
            return arrival_in_ticks;
        }
#endif

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        auto& SetVibrationPath(const VibrationPath& vibration_path_)
        {
            vibration_path = vibration_path_;
            return *this;
        }
#else
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        auto& SetDestinationType(const PositionSourceType destination_type_)
        {
            destination_type = destination_type_;
            return *this;
        }
#else
        auto& SetDestinationType(const Identifier& destination_type_)
        {
            destination_type = destination_type_;
            return *this;
        }
#endif
        auto& SetDestination(const std::shared_ptr<PositionSource>& destination_)
        {
            destination = destination_;
            return *this;
        }

        auto& SetArrivalInTicks(const int arrival_in_ticks_)
        {
            arrival_in_ticks = arrival_in_ticks_;
            return *this;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
            vibration_path = ReadData<VibrationPath>(iter, length);
#else
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            destination_type = ReadData<PositionSourceType, VarInt>(iter, length);
#else
            destination_type = ReadData<Identifier>(iter, length);
#endif
            destination = PositionSource::CreatePositionSource(destination_type);
            destination->Read(iter, length);
            arrival_in_ticks = ReadData<VarInt>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
            WriteData<VibrationPath>(vibration_path, container);
#else
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            WriteData<PositionSourceType, VarInt>(destination_type, container);
#else
            WriteData<Identifier>(destination_type, container);
#endif
            destination->Write(container);
            WriteData<VarInt>(arrival_in_ticks, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
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

    private:
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        VibrationPath vibration_path;
#else
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        PositionSourceType destination_type = PositionSourceType::None;
#else
        Identifier destination_type;
#endif
        std::shared_ptr<PositionSource> destination;
        int arrival_in_ticks = 0;
#endif
    };
}
#endif
