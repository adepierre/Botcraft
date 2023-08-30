#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerCombatEndPacket : public BaseMessage<ClientboundPlayerCombatEndPacket>
    {
    public:
#if   PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x33;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x31;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x32;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x36;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Player Combat End";

        virtual ~ClientboundPlayerCombatEndPacket() override
        {

        }

#if PROTOCOL_VERSION < 763
        void SetKillerId(const int killer_id_)
        {
            killer_id = killer_id_;
        }
#endif

        void SetDuration(const int duration_)
        {
            duration = duration_;
        }


#if PROTOCOL_VERSION < 763
        int GetKillerId() const
        {
            return killer_id;
        }
#endif

        int GetDuration() const
        {
            return duration;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            duration = ReadData<VarInt>(iter, length);
#if PROTOCOL_VERSION < 763
            killer_id = ReadData<int>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(duration, container);
#if PROTOCOL_VERSION < 763
            WriteData<int>(killer_id, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["duration"] = duration;
#if PROTOCOL_VERSION < 763
            output["killer_id"] = killer_id;
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 763
        int killer_id = 0;
#endif
        int duration = 0;

    };
} //ProtocolCraft
#endif
