#include "protocolCraft/MessageFactory.hpp"
#include "protocolCraft/Message.hpp"
#include "protocolCraft/AllClientboundMessages.hpp"

#include "protocolCraft/Utilities/PrivateTemplates.hpp"

namespace ProtocolCraft
{
    std::shared_ptr<Message> CreateClientboundMessage(const ConnectionState state, const int id)
    {
        switch (state)
        {
        case ConnectionState::Login:
            return AutomaticMessageFactory<AllClientboundLoginMessages>(id);
        case ConnectionState::Status:
            return AutomaticMessageFactory<AllClientboundStatusMessages>(id);
        case ConnectionState::Play:
            return AutomaticMessageFactory<AllClientboundPlayMessages>(id);
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        case ConnectionState::Configuration:
            return AutomaticMessageFactory<AllClientboundConfigurationMessages>(id);
#endif
        default:
            return nullptr;
        }
    }
}
