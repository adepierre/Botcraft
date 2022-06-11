#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 758
#include "protocolCraft/Types/NBT/NBT.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundUpdateMobEffectPacket : public BaseMessage<ClientboundUpdateMobEffectPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x4F;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x52;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x58;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x5A;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x59;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x59;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x64;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x65;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x66;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update Mob Effect";
        }

        virtual ~ClientboundUpdateMobEffectPacket() override
        {

        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

#if PROTOCOL_VERSION < 758
        void SetEffectId(const char effect_id_)
        {
            effect_id = effect_id_;
        }
#else
        void SetEffectId(const int effect_id_)
        {
            effect_id = effect_id_;
        }
#endif

        void SetEffectAmplifier(const char effect_amplifier_)
        {
            effect_amplifier = effect_amplifier_;
        }

        void SetEffectDurationTicks(const int effect_duration_ticks_)
        {
            effect_duration_ticks = effect_duration_ticks_;
        }

        void SetFlags(const char flags_)
        {
            flags = flags_;
        }

#if PROTOCOL_VERSION > 758
        void SetFactorData(const NBT& factor_data_)
        {
            factor_data = factor_data_;
        }
#endif


        const int GetEntityId() const
        {
            return entity_id;
        }

#if PROTOCOL_VERSION < 758
        const char GetEffectId() const
        {
            return effect_id;
        }
#else
        const int GetEffectId() const
        {
            return effect_id;
        }
#endif

        const char GetEffectAmplifier() const
        {
            return effect_amplifier;
        }

        const int GetEffectDurationTicks() const
        {
            return effect_duration_ticks;
        }

        const char GetFlags() const
        {
            return flags;
        }

#if PROTOCOL_VERSION > 758
        const NBT& GetFactorData() const
        {
            return factor_data;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadData<VarInt>(iter, length);
#if PROTOCOL_VERSION < 758
            effect_id = ReadData<char>(iter, length);
#else
            effect_id = ReadData<VarInt>(iter, length);
#endif
            effect_amplifier = ReadData<char>(iter, length);
            effect_duration_ticks = ReadData<VarInt>(iter, length);
            flags = ReadData<char>(iter, length);
#if PROTOCOL_VERSION > 758
            const bool has_factor_data = ReadData<bool>(iter, length);
            if (has_factor_data)
            {
                factor_data.Read(iter, length);
            }
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(entity_id, container);
#if PROTOCOL_VERSION < 758
            WriteData<char>(effect_id, container);
#else
            WriteData<VarInt>(effect_id, container);
#endif
            WriteData<char>(effect_amplifier, container);
            WriteData<VarInt>(effect_duration_ticks, container);
            WriteData<char>(flags, container);
#if PROTOCOL_VERSION > 758
            WriteData<bool>(factor_data.HasData(), container);
            if (factor_data.HasData())
            {
                factor_data.Write(container);
            }
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["entity_id"] = entity_id;
            output["effect_id"] = effect_id;
            output["effect_amplifier"] = effect_amplifier;
            output["effect_duration_ticks"] = effect_duration_ticks;
            output["flags"] = flags;
#if PROTOCOL_VERSION > 758
            if (factor_data.HasData())
            {
                output["factor_data"] = factor_data.Serialize();
            }
#endif

            return output;
        }

    private:
        int entity_id;
#if PROTOCOL_VERSION < 758
        char effect_id;
#else
        int effect_id;
#endif
        char effect_amplifier;
        int effect_duration_ticks;
        char flags;
#if PROTOCOL_VERSION > 758
        NBT factor_data;
#endif

    };
} //ProtocolCraft
