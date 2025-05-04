#pragma once

#include "protocolCraft/BasePacket.hpp"

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "protocolCraft/Types/GameProfile/ProfilePublicKey.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundHelloPacket : public BasePacket<ServerboundHelloPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Hello";

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        SERIALIZED_FIELD(GameProfile, std::string);
#elif PROTOCOL_VERSION < 760 /* < 1.19.1 */
        SERIALIZED_FIELD(Name_, std::string);
        SERIALIZED_FIELD(PublicKey, std::optional<ProfilePublicKey>);
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        SERIALIZED_FIELD(Name_, std::string);
        SERIALIZED_FIELD(PublicKey, std::optional<ProfilePublicKey>);
        SERIALIZED_FIELD(ProfileId, std::optional<UUID>);
#elif PROTOCOL_VERSION < 764 /* < 1.20.2 */
        SERIALIZED_FIELD(Name_, std::string);
        SERIALIZED_FIELD(ProfileId, std::optional<UUID>);
#else
        SERIALIZED_FIELD(Name_, std::string);
        SERIALIZED_FIELD(ProfileId, UUID);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
