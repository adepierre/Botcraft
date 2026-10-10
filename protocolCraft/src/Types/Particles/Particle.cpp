#include "protocolCraft/Types/Particles/Particle.hpp"
#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"

#include "protocolCraft/Types/Particles/ParticleOption.hpp"
#include "protocolCraft/Types/Particles/BlockParticleOption.hpp"
#include "protocolCraft/Types/Particles/EmptyParticleOption.hpp"

#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
#include "protocolCraft/Types/Particles/DustParticleOption.hpp"
#include "protocolCraft/Types/Particles/ItemParticleOption.hpp"
#else
#include "protocolCraft/Types/Particles/IconcrackParticleOption.hpp"
#endif

#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/Types/Particles/DustColorTransitionOption.hpp"
#include "protocolCraft/Types/Particles/VibrationParticleOption.hpp"
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/Particles/SculkChargeParticleOption.hpp"
#include "protocolCraft/Types/Particles/ShriekParticleOption.hpp"
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Particles/ColorParticleOption.hpp"
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Types/Particles/TrailParticleOption.hpp"
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "protocolCraft/Types/Particles/PowerParticleOption.hpp"
#include "protocolCraft/Types/Particles/SpellParticleOption.hpp"
#endif
#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
#include "protocolCraft/Types/Particles/GeyserBaseParticleOptions.hpp"
#include "protocolCraft/Types/Particles/GeyserParticleOptions.hpp"
#endif

#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "protocolCraft/Types/Particles/ExplosionParticleInfo.hpp" // Not a particle info type, used in ClientboundExplodePacket
#endif

#include <array>
#include <stdexcept>

namespace ProtocolCraft
{
    // ParticlesOption subtypes
    DEFINE_NETWORK_TYPE(BlockParticleOption);
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    DEFINE_NETWORK_TYPE(ColorParticleOption);
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
    DEFINE_NETWORK_TYPE(DustColorTransitionOption);
#endif
#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
    DEFINE_NETWORK_TYPE(DustParticleOption);
#endif
    DEFINE_NETWORK_TYPE(EmptyParticleOption);
#if PROTOCOL_VERSION < 393 /* < 1.13 */
    DEFINE_NETWORK_TYPE(IconcrackParticleOption);
#endif
#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
    DEFINE_NETWORK_TYPE(ItemParticleOption);
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
    DEFINE_NETWORK_TYPE(VibrationParticleOption);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    DEFINE_NETWORK_TYPE(SculkChargeParticleOption);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    DEFINE_NETWORK_TYPE(ShriekParticleOption);
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    DEFINE_NETWORK_TYPE(TrailParticleOption);
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
    DEFINE_NETWORK_TYPE(PowerParticleOption);
    DEFINE_NETWORK_TYPE(SpellParticleOption);
#endif
#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
    DEFINE_NETWORK_TYPE(GeyserBaseParticleOptions);
    DEFINE_NETWORK_TYPE(GeyserParticleOptions);
#endif

#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
    DEFINE_NETWORK_TYPE(ExplosionParticleInfo); // Not a particle info type, used in ClientboundExplodePacket
#endif


    std::shared_ptr<ParticleOption> Particle::CreateParticleOption(const ProtocolCraft::ParticleType type)
    {
        if (type <= ParticleType::None || type >= ParticleType::NUM_PARTICLE_TYPES)
        {
            throw std::runtime_error("Unable to create particle with id: " + std::to_string(static_cast<int>(type)) + ".");
        }

        switch (type)
        {
#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
        case ParticleType::Block:
        case ParticleType::FallingDust:
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        case ParticleType::BlockMarker:
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        case ParticleType::DustPillar:
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        case ParticleType::BlockCrumble:
#endif
            return std::make_shared<BlockParticleOption>();
        case ParticleType::Dust:
            return std::make_shared<DustParticleOption>();
        case ParticleType::Item:
            return std::make_shared<ItemParticleOption>();
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        case ParticleType::DustColorTransition:
            return std::make_shared<DustColorTransitionOption>();
        case ParticleType::Vibration:
            return std::make_shared<VibrationParticleOption>();
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        case ParticleType::SculkCharge:
            return std::make_shared<SculkChargeParticleOption>();
        case ParticleType::Shriek:
            return std::make_shared<ShriekParticleOption>();
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        case ParticleType::EntityEffect:
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        case ParticleType::TintedLeaves:
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        case ParticleType::Flash:
#endif
            return std::make_shared<ColorParticleOption>();
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        case ParticleType::Trail:
            return std::make_shared<TrailParticleOption>();
#endif
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        case ParticleType::DragonBreath:
            return std::make_shared<PowerParticleOption>();
        case ParticleType::Effect:
        case ParticleType::InstantEffect:
            return std::make_shared<SpellParticleOption>();
#endif
#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
        case ParticleType::GeyserBase:
        case ParticleType::GeyserPoof:
            return std::make_shared<GeyserBaseParticleOptions>();
        case ParticleType::Geyser:
        case ParticleType::GeyserPlume:
            return std::make_shared<GeyserParticleOptions>();
#endif
#else //1.12.2
        case ParticleType::Blockcrack:
        case ParticleType::Blockdust:
        case ParticleType::FallingDust:
            return std::make_shared<BlockParticleOption>();
        case ParticleType::Iconcrack:
            return std::make_shared<IconcrackParticleOption>();
#endif
        default:
            return std::make_shared<EmptyParticleOption>();
        }
    }

    DEFINE_NETWORK_TYPE(Particle);
}
