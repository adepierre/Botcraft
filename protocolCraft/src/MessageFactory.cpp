#include "protocolCraft/MessageFactory.hpp"
#include "protocolCraft/Message.hpp"
#include "protocolCraft/AllClientboundMessages.hpp"
#include "protocolCraft/AllServerboundMessages.hpp"

namespace ProtocolCraft
{
    namespace
    {
        template<typename TypesTuple>
        std::shared_ptr<Message> AutomaticMessageFactory(const int id)
        {
            std::shared_ptr<Message> output = nullptr;

            Internal::loop<std::tuple_size_v<TypesTuple>>([&](auto i) {
                if (id == i)
                {
                    output = std::make_shared<std::tuple_element_t<i, TypesTuple>>();
                }
            });

            return output;
        }
    }

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

    std::shared_ptr<Message> CreateServerboundMessage(const ConnectionState state, const int id)
    {
        switch (state)
        {
        case ConnectionState::Handshake:
            return AutomaticMessageFactory<AllServerboundHandshakingMessages>(id);
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
