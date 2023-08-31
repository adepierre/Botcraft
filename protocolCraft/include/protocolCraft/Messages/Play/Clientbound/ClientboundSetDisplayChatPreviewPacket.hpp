#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetDisplayChatPreviewPacket : public BaseMessage<ClientboundSetDisplayChatPreviewPacket>
    {
    public:
#if   PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x4B;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x4E;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Display Chat Preview";

        virtual ~ClientboundSetDisplayChatPreviewPacket() override
        {

        }

        void SetEnabled(const bool enabled_)
        {
            enabled = enabled_;
        }


        bool GetEnabled() const
        {
            return enabled;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            enabled = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(enabled, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["enabled"] = enabled;


            return output;
        }

    private:
        bool enabled = false;

    };
} //ProtocolCraft
#endif
