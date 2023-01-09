#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/Slot.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class AdvancementDisplay : public NetworkType
    {
    public:
        virtual ~AdvancementDisplay() override
        {

        }

        void SetTitle(const Chat& title_)
        {
            title = title_;
        }

        void SetDescription(const Chat& description_)
        {
            description = description_;
        }

        void SetIcon(const Slot& icon_)
        {
            icon = icon_;
        }

        void SetFrameType(const int frame_type_)
        {
            frame_type = frame_type_;
        }

        void SetFlags(const int flags_)
        {
            flags = flags_;
        }

        void SetBackgroundTexture(const Identifier& background_texture_)
        {
            background_texture = background_texture_;
        }

        void SetXCoord(const float x_coord_)
        {
            x_coord = x_coord_;
        }
        
        void SetYCoord(const float y_coord_)
        {
            y_coord = y_coord_;
        }


        const Chat& GetTitle() const
        {
            return title;
        }

        const Chat& GetDescription() const
        {
            return description;
        }

        const Slot& GetIcon() const
        {
            return icon;
        }

        int GetFrameType() const
        {
            return frame_type;
        }

        int GetFlags() const
        {
            return flags;
        }
        
        const Identifier& GetBackgroundTexture() const
        {
            return background_texture;
        }

        float GetXCoord() const
        {
            return x_coord;
        }
        
        float GetYCoord() const
        {
            return y_coord;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            title = ReadData<Chat>(iter, length);
            description = ReadData<Chat>(iter, length);
            icon = ReadData<Slot>(iter, length);
            frame_type = ReadData<VarInt>(iter, length);
            flags = ReadData<int>(iter, length);
            if (flags & 0x01)
            {
                background_texture = ReadData<Identifier>(iter, length);
            }
            x_coord = ReadData<float>(iter, length);
            y_coord = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<Chat>(title, container);
            WriteData<Chat>(description, container);
            WriteData<Slot>(icon, container);
            WriteData<VarInt>(frame_type, container);
            WriteData<int>(flags, container);
            if (flags & 0x01)
            {
                WriteData<Identifier>(background_texture, container);
            }
            WriteData<float>(x_coord, container);
            WriteData<float>(y_coord, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["title"] = title.Serialize();
            output["description"] = description.Serialize();
            output["icon"] = icon.Serialize();
            output["frame_type"] = frame_type;
            output["flags"] = flags;
            if (flags & 0x01)
            {
                output["background_texture"] = background_texture.Serialize();
            }
            output["x_coord"] = x_coord;
            output["y_coord"] = y_coord;

            return output;
        }

    private:
        Chat title;
        Chat description;
        Slot icon;
        int frame_type;
        int flags;
        Identifier background_texture;
        float x_coord;
        float y_coord;
    };
}