#pragma once

#if PROTOCOL_VERSION < 755
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundContainerAckPacket : public BaseMessage<ServerboundContainerAckPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x06;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498 || PROTOCOL_VERSION == 573 ||  \
      PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 ||  \
      PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x07;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Container Ack";

        void SetContainerId(const char c)
        {
            container_id = c;
        }

        void SetUid(const short s)
        {
            uid = s;
        }

        void SetAccepted(const bool b)
        {
            accepted = b;
        }

        char GetContainerId() const
        {
            return container_id;
        }

        short GetUid() const
        {
            return uid;
        }

        bool GetAccepted() const
        {
            return accepted;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            container_id = ReadData<char>(iter, length);
            uid = ReadData<short>(iter, length);
            accepted = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<char>(container_id, container);
            WriteData<short>(uid, container);
            WriteData<bool>(accepted, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["container_id"] = container_id;
            output["uid"] = uid;
            output["accepted"] = accepted;

            return output;
        }

    private:
        char container_id = 0;
        short uid = 0;
        bool accepted = false;
    };
} //ProtocolCraft
#endif
