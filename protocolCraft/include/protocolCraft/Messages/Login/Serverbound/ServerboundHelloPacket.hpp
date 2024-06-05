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
        static constexpr int packet_id = 0x00;
        static constexpr std::string_view packet_name = "Hello";

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS_TYPES(std::string);
        DECLARE_FIELDS_NAMES(GameProfile);
#elif PROTOCOL_VERSION < 760 /* < 1.19.1 */
        DECLARE_FIELDS_TYPES(std::string, std::optional<ProfilePublicKey>);
        DECLARE_FIELDS_NAMES(Name_,       PublicKey);
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS_TYPES(std::string, std::optional<ProfilePublicKey>, std::optional<UUID>);
        DECLARE_FIELDS_NAMES(Name_,       PublicKey,                       ProfileId);
#elif PROTOCOL_VERSION < 764 /* < 1.20.2 */
        DECLARE_FIELDS_TYPES(std::string, std::optional<UUID>);
        DECLARE_FIELDS_NAMES(Name_,       ProfileId);
#else
        DECLARE_FIELDS_TYPES(std::string, UUID);
        DECLARE_FIELDS_NAMES(Name_,       ProfileId);
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
