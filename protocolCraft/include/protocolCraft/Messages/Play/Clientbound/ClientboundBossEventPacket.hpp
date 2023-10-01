#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundBossEventPacket : public BaseMessage<ClientboundBossEventPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */ || PROTOCOL_VERSION == 393 /* 1.13 */ ||  \
      PROTOCOL_VERSION == 401 /* 1.13.1 */ || PROTOCOL_VERSION == 404 /* 1.13.2 */ ||  \
      PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 759 /* 1.19 */ || PROTOCOL_VERSION == 760 /* 1.19.1/2 */ ||  \
      PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x0A;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x0A;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Boss Event";

        virtual ~ClientboundBossEventPacket() override
        {

        }

        void SetId_(const UUID& id__)
        {
            id_ = id__;
        }

        void SetOperation(const int operation_)
        {
            operation = operation_;
        }

        void SetName_(const Chat& name__)
        {
            name_ = name__;
        }

        void SetPct(const float pct_)
        {
            pct = pct_;
        }

        void SetColor(const int color_)
        {
            color = color_;
        }

        void SetOverlay(const int overlay_)
        {
            overlay = overlay_;
        }

        void SetFlags(const unsigned char flags_)
        {
            flags = flags_;
        }


        const UUID& GetId_() const
        {
            return id_;
        }

        int GetOperation() const
        {
            return operation;
        }

        const Chat& GetName_() const
        {
            return name_;
        }

        float GetPct() const
        {
            return pct;
        }

        int GetColor() const
        {
            return color;
        }

        int GetOverlay() const
        {
            return overlay;
        }

        unsigned char GetFlags() const
        {
            return flags;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadData<UUID>(iter, length);
            operation = ReadData<VarInt>(iter, length);
            switch (operation)
            {
            case 0:
                name_ = ReadData<Chat>(iter, length);
                pct = ReadData<float>(iter, length);
                color = ReadData<VarInt>(iter, length);
                overlay = ReadData<VarInt>(iter, length);
                flags = ReadData<unsigned char>(iter, length);
                break;
            case 1:
                break;
            case 2:
                pct = ReadData<float>(iter, length);
                break;
            case 3:
                name_ = ReadData<Chat>(iter, length);
                break;
            case 4:
                color = ReadData<VarInt>(iter, length);
                overlay = ReadData<VarInt>(iter, length);
                break;
            case 5:
                flags = ReadData<unsigned char>(iter, length);
                break;
            default:
                break;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<UUID>(id_, container);
            WriteData<VarInt>(operation, container);
            switch (operation)
            {
            case 0:
                WriteData<Chat>(name_, container);
                WriteData<float>(pct, container);
                WriteData<VarInt>(color, container);
                WriteData<VarInt>(overlay, container);
                WriteData<unsigned char>(flags, container);
                break;
            case 1:
                break;
            case 2:
                WriteData<float>(pct, container);
                break;
            case 3:
                WriteData<Chat>(name_, container);
                break;
            case 4:
                WriteData<VarInt>(color, container);
                WriteData<VarInt>(overlay, container);
                break;
            case 5:
                WriteData<unsigned char>(flags, container);
                break;
            default:
                break;
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["id_"] = id_;
            output["operation"] = operation;

            switch (operation)
            {
            case 0:
                output["name_"] = name_;
                output["pct"] = pct;
                output["color"] = color;
                output["overlay"] = overlay;
                output["flags"] = flags;
                break;
            case 1:
                break;
            case 2:
                output["pct"] = pct;
                break;
            case 3:
                output["name_"] = name_;
                break;
            case 4:
                output["color"] = color;
                output["overlay"] = overlay;
                break;
            case 5:
                output["flags"] = flags;
                break;
            default:
                break;
            }

            return output;
        }

    private:
        UUID id_ = {};
        int operation = 0;
        Chat name_;
        float pct = 0.0f;
        int color = 0;
        int overlay = 0;
        unsigned char flags = 0;

    };
} //ProtocolCraft
