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
            return AutomaticMessageFactory<AllServerboundHandshakeMessages>(id);
        case ConnectionState::Login:
            return AutomaticMessageFactory<AllServerboundLoginMessages>(id);
        case ConnectionState::Status:
            return AutomaticMessageFactory<AllServerboundStatusMessages>(id);
        case ConnectionState::Play:
            return AutomaticMessageFactory<AllServerboundPlayMessages>(id);
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        case ConnectionState::Configuration:
            return AutomaticMessageFactory<AllServerboundConfigurationMessages>(id);
#endif
        default:
            return nullptr;
        }
    }
}
