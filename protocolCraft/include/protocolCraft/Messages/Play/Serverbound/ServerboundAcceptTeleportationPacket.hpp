#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundAcceptTeleportationPacket : public BaseMessage<ServerboundAcceptTeleportationPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 || PROTOCOL_VERSION == 393 ||  \
      PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 ||  \
      PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498 || PROTOCOL_VERSION == 573 ||  \
      PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 ||  \
      PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754 || PROTOCOL_VERSION == 755 ||  \
      PROTOCOL_VERSION == 756 || PROTOCOL_VERSION == 757 ||  \
      PROTOCOL_VERSION == 758 || PROTOCOL_VERSION == 759 ||  \
      PROTOCOL_VERSION == 760 || PROTOCOL_VERSION == 761 ||  \
      PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x00;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Accept Teleportation";

        virtual ~ServerboundAcceptTeleportationPacket() override
        {

        }

        void SetId_(const int i)
        {
            id_ = i;
        }

        int GetId_() const
        {
            return id_;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            id_ = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(id_, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["id_"] = id_;

            return output;
        }

    private:
        int id_ = 0;
    };
} //ProtocolCraft
