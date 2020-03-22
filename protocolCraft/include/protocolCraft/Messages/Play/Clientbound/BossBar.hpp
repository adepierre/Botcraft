#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat.hpp"

namespace ProtocolCraft
{
    enum class BossBarAction
    {
        Add = 0,
        Remove = 1,
        UpdateHealth = 2,
        UpdateTitle = 3,
        UpdateStyle = 4,
        UpdateFlags = 5
    };

    class BossBar : public BaseMessage<BossBar>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x0C;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x0C;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x0C;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x0D;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Boss Bar";
        }

        void SetUuid(const UUID& uuid_)
        {
            uuid = uuid_;
        }

        void SetAction(const int action_)
        {
            action = action_;
        }

        void SetTitle(const Chat& title_)
        {
            title = title_;
        }

        void SetHealth(const float health_)
        {
            health = health_;
        }

        void SetColor(const int color_)
        {
            color = color_;
        }

        void SetDivision(const int division_)
        {
            division = division_;
        }

        void SetFlags(const unsigned char flags_)
        {
            flags = flags_;
        }


        const UUID& GetUuid() const
        {
            return uuid;
        }

        const int GetAction() const
        {
            return action;
        }

        const Chat& GetTitle() const
        {
            return title;
        }

        const float GetHealth() const
        {
            return health;
        }

        const int GetColor() const
        {
            return color;
        }

        const int GetDivision() const
        {
            return division;
        }

        const unsigned char GetFlags() const
        {
            return flags;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            uuid = ReadUUID(iter, length);
            action = ReadVarInt(iter, length);
            switch ((BossBarAction)action)
            {
            case BossBarAction::Add:
                title.Read(iter, length);
                health = ReadData<float>(iter, length);
                color = ReadVarInt(iter, length);
                division = ReadVarInt(iter, length);
                flags = ReadData<unsigned char>(iter, length);
                break;
            case BossBarAction::Remove:
                break;
            case BossBarAction::UpdateHealth:
                health = ReadData<float>(iter, length);
                break;
            case BossBarAction::UpdateTitle:
                title.Read(iter, length);
                break;
            case BossBarAction::UpdateStyle:
                color = ReadVarInt(iter, length);
                division = ReadVarInt(iter, length);
                break;
            case BossBarAction::UpdateFlags:
                flags = ReadData<unsigned char>(iter, length);
                break;
            default:
                break;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteUUID(uuid, container);
            WriteVarInt(action, container);
            switch ((BossBarAction)action)
            {
            case BossBarAction::Add:
                title.Write(container);
                WriteData<float>(health, container);
                WriteVarInt(color, container);
                WriteVarInt(division, container);
                WriteData<unsigned char>(flags, container);
                break;
            case BossBarAction::Remove:
                break;
            case BossBarAction::UpdateHealth:
                WriteData<float>(health, container);
                break;
            case BossBarAction::UpdateTitle:
                title.Write(container);
                break;
            case BossBarAction::UpdateStyle:
                WriteVarInt(color, container);
                WriteVarInt(division, container);
                break;
            case BossBarAction::UpdateFlags:
                WriteData<unsigned char>(flags, container);
                break;
            default:
                break;
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["uuid"] = picojson::value(uuid);
            object["action"] = picojson::value((double)action);

            switch ((BossBarAction)action)
            {
            case BossBarAction::Add:
                object["title"] = title.Serialize();
                object["health"] = picojson::value((double)health);
                object["color"] = picojson::value((double)color);
                object["division"] = picojson::value((double)division);
                object["flags"] = picojson::value((double)flags);
                break;
            case BossBarAction::Remove:
                break;
            case BossBarAction::UpdateHealth:
                object["health"] = picojson::value((double)health);
                break;
            case BossBarAction::UpdateTitle:
                object["title"] = title.Serialize();
                break;
            case BossBarAction::UpdateStyle:
                object["color"] = picojson::value((double)color);
                object["division"] = picojson::value((double)division);
                break;
            case BossBarAction::UpdateFlags:
                object["flags"] = picojson::value((double)flags);
                break;
            default:
                break;
            }

            return value;
        }

    private:
        UUID uuid;
        int action;
        Chat title;
        float health;
        int color;
        int division;
        unsigned char flags;

    };
} //ProtocolCraft