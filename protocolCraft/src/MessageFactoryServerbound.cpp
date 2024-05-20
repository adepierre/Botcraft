#include "protocolCraft/MessageFactory.hpp"
#include "protocolCraft/Message.hpp"
#include "protocolCraft/AllServerboundMessages.hpp"

#include "protocolCraft/Utilities/PrivateTemplates.hpp"

namespace ProtocolCraft
{
    std::shared_ptr<Message> CreateServerboundMessage(const ConnectionState state, const int id)
    {
        switch (state)
        {
        case ConnectionState::Handshake:
            return Internal::AutomaticMessageFactory<AllServerboundHandshakeMessages>(id);
        case ConnectionState::Login:
            return Internal::AutomaticMessageFactory<AllServerboundLoginMessages>(id);
        case ConnectionState::Status:
            return Internal::AutomaticMessageFactory<AllServerboundStatusMessages>(id);
        case ConnectionState::Play:
            return Internal::AutomaticMessageFactory<AllServerboundPlayMessages>(id);
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        case ConnectionState::Configuration:
            return Internal::AutomaticMessageFactory<AllServerboundConfigurationMessages>(id);
#endif
        default:
            return nullptr;
        }
    }
}
