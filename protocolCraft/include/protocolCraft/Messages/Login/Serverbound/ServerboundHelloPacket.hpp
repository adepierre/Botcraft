#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/GameProfile/ProfilePublicKey.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundHelloPacket : public BaseMessage<ServerboundHelloPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Hello";

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS(
            (std::string),
            (GameProfile)
        );
#elif PROTOCOL_VERSION < 760 /* < 1.19.1 */
        DECLARE_FIELDS(
            (std::string, std::optional<ProfilePublicKey>),
            (Name_,       PublicKey)
        );
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS(
            (std::string, std::optional<ProfilePublicKey>, std::optional<UUID>),
            (Name_,       PublicKey,                       ProfileId)
        );
#elif PROTOCOL_VERSION < 764 /* < 1.20.2 */
        DECLARE_FIELDS(
            (std::string, std::optional<UUID>),
            (Name_,       ProfileId)
        );
#else
        DECLARE_FIELDS(
            (std::string, UUID),
            (Name_,       ProfileId)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        GETTER_SETTER(GameProfile);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        GETTER_SETTER(Name_);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
        GETTER_SETTER(PublicKey);
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
        GETTER_SETTER(ProfileId);
#endif
    };
} // ProtocolCraft
