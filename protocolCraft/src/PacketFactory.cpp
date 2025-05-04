#include "protocolCraft/PacketFactory.hpp"
#include "protocolCraft/Packet.hpp"
#include "protocolCraft/AllClientboundPackets.hpp"
#include "protocolCraft/AllServerboundPackets.hpp"

namespace ProtocolCraft
{
    namespace
    {
        template<typename TypesTuple>
        std::shared_ptr<Packet> AutomaticPacketFactory(const int id)
        {
            std::shared_ptr<Packet> output = nullptr;

            Internal::loop<std::tuple_size_v<TypesTuple>>([&](auto i) {
                if (id == i)
                {
                    output = std::make_shared<std::tuple_element_t<i, TypesTuple>>();
                }
            });

            return output;
        }
    }

    std::shared_ptr<Packet> CreateClientboundPacket(const ConnectionState state, const int id)
    {
        switch (state)
        {
        case ConnectionState::Login:
            return AutomaticPacketFactory<AllClientboundLoginPackets>(id);
        case ConnectionState::Status:
            return AutomaticPacketFactory<AllClientboundStatusPackets>(id);
        case ConnectionState::Play:
            return AutomaticPacketFactory<AllClientboundPlayPackets>(id);
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        case ConnectionState::Configuration:
            return AutomaticPacketFactory<AllClientboundConfigurationPackets>(id);
#endif
        default:
            return nullptr;
        }
    }

    std::shared_ptr<Packet> CreateServerboundPacket(const ConnectionState state, const int id)
    {
        switch (state)
        {
        case ConnectionState::Handshake:
            return AutomaticPacketFactory<AllServerboundHandshakingPackets>(id);
        case ConnectionState::Login:
            return AutomaticPacketFactory<AllServerboundLoginPackets>(id);
        case ConnectionState::Status:
            return AutomaticPacketFactory<AllServerboundStatusPackets>(id);
        case ConnectionState::Play:
            return AutomaticPacketFactory<AllServerboundPlayPackets>(id);
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        case ConnectionState::Configuration:
            return AutomaticPacketFactory<AllServerboundConfigurationPackets>(id);
#endif
        default:
            return nullptr;
        }
    }
}
