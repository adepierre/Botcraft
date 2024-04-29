#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPongConfigurationPacket : public BaseMessage<ServerboundPongConfigurationPacket>
    {
    public:
#if   PROTOCOL_VERSION < 766 /* < 1.20.5 */
        static constexpr int packet_id = 0x04;
#elif PROTOCOL_VERSION == 766 /* 1.20.5 */
        static constexpr int packet_id = 0x05;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Pong (Configuration)";

        virtual ~ServerboundPongConfigurationPacket() override
        {

        }

        void SetId_(const int id__)
        {
            id_ = id__;
        }


        int GetId_() const
        {
            return id_;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<int>(id_, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["id"] = id_;

            return output;
        }

    private:
        int id_ = 0;

    };
} //ProtocolCraft
#endif
