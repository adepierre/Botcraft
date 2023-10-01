#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundResourcePackConfigurationPacket : public BaseMessage<ServerboundResourcePackConfigurationPacket>
    {
    public:
        static constexpr int packet_id = 0x05;

        static constexpr std::string_view packet_name = "Resource Pack (Configuration)";

        virtual ~ServerboundResourcePackConfigurationPacket() override
        {

        }

        void SetAction(const int action_)
        {
            action = action_;
        }


        int GetAction() const
        {
            return action;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            action = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(action, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["action"] = action;

            return output;
        }

    private:
        int action = 0;

    };
} //ProtocolCraft
#endif
