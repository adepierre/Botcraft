#pragma once

#if PROTOCOL_VERSION > 351 /* > 1.12.2 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerLookAtPacket : public BaseMessage<ClientboundPlayerLookAtPacket>
    {
    public:
#if   PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x31;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x33;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x37;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x38;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x37;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x3B;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3 */
        static constexpr int packet_id = 0x3D;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Face Player";

        virtual ~ClientboundPlayerLookAtPacket() override
        {

        }

        void SetX(const double x_)
        {
            x = x_;
        }

        void SetY(const double y_)
        {
            y = y_;
        }

        void SetZ(const double z_)
        {
            z = z_;
        }

        void SetEntity(const int entity_)
        {
            entity = entity_;
        }

        void SetFromAnchor(const int from_anchor_)
        {
            from_anchor = from_anchor_;
        }

        void SetToAnchor(const int to_anchor_)
        {
            to_anchor = to_anchor_;
        }

        void SetAtEntity(const bool at_entity_)
        {
            at_entity = at_entity_;
        }


        double GetX() const
        {
            return x;
        }

        double GetY() const
        {
            return y;
        }

        double GetZ() const
        {
            return z;
        }

        int GetEntity() const
        {
            return entity;
        }

        int GetFromAnchor() const
        {
            return from_anchor;
        }

        int GetToAnchor() const
        {
            return to_anchor;
        }

        bool GetAtEntity() const
        {
            return at_entity;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            from_anchor = ReadData<VarInt>(iter, length);
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            at_entity = ReadData<bool>(iter, length);
            if (at_entity)
            {
                entity = ReadData<VarInt>(iter, length);
                to_anchor = ReadData<VarInt>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(from_anchor, container);
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<bool>(at_entity, container);
            if (at_entity)
            {
                WriteData<VarInt>(entity, container);
                WriteData<VarInt>(to_anchor, container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["from_anchor"] = from_anchor;
            output["x"] = x;
            output["y"] = y;
            output["z"] = z;
            output["at_entity"] = at_entity;
            if (at_entity)
            {
                output["entity"] = entity;
                output["to_anchor"] = to_anchor;
            }

            return output;
        }

    private:
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        int entity = 0;
        int from_anchor = 0;
        int to_anchor = 0;
        bool at_entity = false;

    };
} //ProtocolCraft
#endif
