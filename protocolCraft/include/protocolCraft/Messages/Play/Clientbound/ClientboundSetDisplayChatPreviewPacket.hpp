#if PROTOCOL_VERSION > 758 && PROTOCOL_VERSION < 761
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetDisplayChatPreviewPacket : public BaseMessage<ClientboundSetDisplayChatPreviewPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 759 // 1.19
            return 0x4B;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x4E;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Display Chat Preview";
        }

        virtual ~ClientboundSetDisplayChatPreviewPacket() override
        {

        }

        void SetEnabled(const bool enabled_)
        {
            enabled = enabled_;
        }


        const bool GetEnabled() const
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

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["enabled"] = enabled;


            return output;
        }

    private:
        bool enabled;

    };
} //ProtocolCraft
#endif
