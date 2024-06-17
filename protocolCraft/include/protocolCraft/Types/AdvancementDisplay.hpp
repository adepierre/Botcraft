#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class AdvancementDisplay : public NetworkType
    {
        DECLARE_FIELDS(
            (Chat,  Chat,        Slot, VarInt,    int,   std::optional<Identifier>, float,  float),
            (Title, Description, Icon, FrameType, Flags, BackgroundTexture,         XCoord, YCoord)
        );
        // Manually declare read/write because of the flags thing
        DECLARE_SERIALIZE;

        GETTER_SETTER(Title);
        GETTER_SETTER(Description);
        GETTER_SETTER(Icon);
        GETTER_SETTER(FrameType);
        GETTER_SETTER(Flags);
    public:
        const std::optional<Identifier>& GetBackgroundTexture() const
        {
            return std::get<static_cast<size_t>(FieldsEnum::BackgroundTexture)>(fields);
        }

        auto& SetBackgroundTexture(const std::optional<Identifier>& BackgroundTexture)
        {
            SetFlags(BackgroundTexture.has_value() ? (GetFlags() | 0x01) : (GetFlags() & ~0x01));
            std::get<static_cast<size_t>(FieldsEnum::BackgroundTexture)>(fields) = BackgroundTexture;
            return *this;
        }
        GETTER_SETTER(XCoord);
        GETTER_SETTER(YCoord);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetTitle(ReadData<Chat>(iter, length));
            SetDescription(ReadData<Chat>(iter, length));
            SetIcon(ReadData<Slot>(iter, length));
            SetFrameType(ReadData<VarInt>(iter, length));
            SetFlags(ReadData<int>(iter, length));
            if (GetFlags() & 0x01)
            {
                SetBackgroundTexture(ReadData<Identifier>(iter, length));
            }
            else
            {
                SetBackgroundTexture(std::optional<Identifier>());
            }
            SetXCoord(ReadData<float>(iter, length));
            SetYCoord(ReadData<float>(iter, length));
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Chat>(GetTitle(), container);
            WriteData<Chat>(GetDescription(), container);
            WriteData<Slot>(GetIcon(), container);
            WriteData<VarInt>(GetFrameType(), container);
            WriteData<int>(GetFlags(), container);
            if (GetFlags() & 0x01) // Should always have value if flags 0x01 is set
            {
                WriteData<Identifier>(GetBackgroundTexture().value(), container);
            }
            WriteData<float>(GetXCoord(), container);
            WriteData<float>(GetYCoord(), container);
        }
    };
}
