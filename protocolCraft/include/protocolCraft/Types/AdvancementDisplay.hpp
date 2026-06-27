#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#if PROTOCOL_VERSION < 775 /* < 26.1 */
#include "protocolCraft/Types/Item/Slot.hpp"
#else
#include "protocolCraft/Types/Item/ItemStackTemplate.hpp"
#endif
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class AdvancementDisplay : public NetworkType
    {
        DEFINE_CONDITION(HasBackgroundTexture, GetFlags() & 0x01);

        SERIALIZED_FIELD(Title, Chat);
        SERIALIZED_FIELD(Description, Chat);
#if PROTOCOL_VERSION < 775 /* < 26.1 */
        SERIALIZED_FIELD(Icon, Slot);
#else
        SERIALIZED_FIELD(Icon, ItemStackTemplate);
#endif
        SERIALIZED_FIELD(FrameType, VarInt);
        SERIALIZED_FIELD(Flags, int);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(BackgroundTexture, Internal::Conditioned<Identifier, &AdvancementDisplay::HasBackgroundTexture>);
        SERIALIZED_FIELD(XCoord, float);
        SERIALIZED_FIELD(YCoord, float);

        DECLARE_READ_WRITE_SERIALIZE;

        GETTER(BackgroundTexture);
    public:
        auto& SetBackgroundTexture(const std::optional<Identifier>& BackgroundTexture_)
        {
            SetFlags(BackgroundTexture_.has_value() ? (GetFlags() | 0x01) : (GetFlags() & ~0x01));
            BackgroundTexture = BackgroundTexture_;
            return *this;
        }
    };
}
