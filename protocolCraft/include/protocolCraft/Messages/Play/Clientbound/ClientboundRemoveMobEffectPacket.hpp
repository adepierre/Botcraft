#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundRemoveMobEffectPacket : public BaseMessage<ClientboundRemoveMobEffectPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x33;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x36;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x38;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x39;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x38;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x37;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x3B;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x3B;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x39;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x3C;
#elif PROTOCOL_VERSION == 761 // 1.19.3
            return 0x3B;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Remove Mob Effect";
        }

        virtual ~ClientboundRemoveMobEffectPacket() override
        {

        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

#if PROTOCOL_VERSION < 758
        void SetEffect(const char effect_)
        {
            effect = effect_;
        }
#else
        void SetEffect(const int effect_)
        {
            effect = effect_;
        }
#endif


        const int GetEntityId() const
        {
            return entity_id;
        }

#if PROTOCOL_VERSION < 758
        const char GetEffect() const
        {
            return effect;
        }
#else
        const int GetEffect() const
        {
            return effect;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadData<VarInt>(iter, length);
#if PROTOCOL_VERSION < 758
            effect = ReadData<char>(iter, length);
#else
            effect = ReadData<VarInt>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(entity_id, container);
#if PROTOCOL_VERSION < 758
            WriteData<char>(effect, container);
#else
            WriteData<VarInt>(effect, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["entity_id"] = entity_id;
            output["effect"] = effect;

            return output;
        }

    private:
        int entity_id;
#if PROTOCOL_VERSION < 758
        char effect;
#else
        int effect;
#endif

    };
} //ProtocolCraft