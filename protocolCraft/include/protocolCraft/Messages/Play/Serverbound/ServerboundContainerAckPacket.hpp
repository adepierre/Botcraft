#pragma once

#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundContainerAckPacket : public BaseMessage<ServerboundContainerAckPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x06;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */ ||  \
      PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
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
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            container_id = ReadData<char>(iter, length);
            uid = ReadData<short>(iter, length);
            accepted = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
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
