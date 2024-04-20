#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/Types/Particles/Particle.hpp"

#if PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Types/Vibrations/VibrationPath.hpp"
#else
#include "protocolCraft/Types/Vibrations/PositionSource.hpp"
#endif

namespace ProtocolCraft
{
    class VibrationParticle : public Particle
    {
    public:
        VibrationParticle();
        
        virtual ~VibrationParticle();
        
        virtual std::string GetName() const override;
        
        virtual ParticleType GetType() const override;

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        const VibrationPath& GetVibrationPath() const;
#else
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        PositionSourceType GetDestinationType() const;
#else
        const Identifier& GetDestinationType() const;
#endif
        const std::shared_ptr<PositionSource>& GetDestination() const;
        int GetArrivalInTicks() const;
#endif

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        void SetVibrationPath(const VibrationPath& vibration_path_);
#else
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        void SetDestinationType(const PositionSourceType destination_type_);
#else
        void SetDestinationType(const Identifier& destination_type_);
#endif
        void SetDestination(const std::shared_ptr<PositionSource>& destination_);
        void SetArrivalInTicks(const int arrival_in_ticks_);
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
        
        virtual void WriteImpl(WriteContainer& container) const override;
        
        virtual Json::Value SerializeImpl() const override;

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
