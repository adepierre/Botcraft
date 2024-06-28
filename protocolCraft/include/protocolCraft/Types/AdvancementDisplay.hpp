#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class AdvancementDisplay : public NetworkType
    {
        DECLARE_CONDITION(HasBackgroundTexture, GetFlags() & 0x01);

        DECLARE_FIELDS(
            (Chat,  Chat,        Slot, VarInt,    int,   Internal::Conditioned<Identifier, &AdvancementDisplay::HasBackgroundTexture>, float,  float),
            (Title, Description, Icon, FrameType, Flags, BackgroundTexture,                                                            XCoord, YCoord)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Title);
        GETTER_SETTER(Description);
        GETTER_SETTER(Icon);
        GETTER_SETTER(FrameType);
        GETTER_SETTER(Flags);
        GETTER_SETTER(XCoord);
        GETTER_SETTER(YCoord);
        GETTER       (BackgroundTexture);
    public:
        auto& SetBackgroundTexture(const std::optional<Identifier>& BackgroundTexture)
        {
            SetFlags(BackgroundTexture.has_value() ? (GetFlags() | 0x01) : (GetFlags() & ~0x01));
            std::get<static_cast<size_t>(FieldsEnum::BackgroundTexture)>(fields) = BackgroundTexture;
            return *this;
        }
    };
}
