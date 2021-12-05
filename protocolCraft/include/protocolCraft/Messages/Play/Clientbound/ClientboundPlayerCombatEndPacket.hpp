#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerCombatEndPacket : public BaseMessage<ClientboundPlayerCombatEndPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x33;
#elif PROTOCOL_VERSION == 757 // 1.18
            return 0x33;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Combat End";
        }

        virtual ~ClientboundPlayerCombatEndPacket() override
        {

        }

        void SetKillerId(const int killer_id_)
        {
            killer_id = killer_id_;
        }

        void SetDuration(const int duration_)
        {
            duration = duration_;
        }


        const int GetKillerId() const
        {
            return killer_id;
        }

        const int GetDuration() const
        {
            return duration;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            duration = ReadData<VarInt>(iter, length);
            killer_id = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(duration, container);
            WriteData<int>(killer_id, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["duration"] = duration;
            output["killer_id"] = killer_id;

            return output;
        }

    private:
        int killer_id;
        int duration;

    };
} //ProtocolCraft
#endif