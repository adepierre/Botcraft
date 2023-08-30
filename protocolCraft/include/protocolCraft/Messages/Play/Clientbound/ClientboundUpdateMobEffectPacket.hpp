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
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x4F;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x52;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x58;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x5A;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x59;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756
        static constexpr int packet_id = 0x64;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x65;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x66;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x69;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x68;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x6C;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Update Mob Effect";

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
        void SetFactorData(const std::optional<NBT::Value>& factor_data_)
        {
            factor_data = factor_data_;
        }
#endif


        int GetEntityId() const
        {
            return entity_id;
        }

#if PROTOCOL_VERSION < 758
        char GetEffectId() const
        {
            return effect_id;
        }
#else
        int GetEffectId() const
        {
            return effect_id;
        }
#endif

        char GetEffectAmplifier() const
        {
            return effect_amplifier;
        }

        int GetEffectDurationTicks() const
        {
            return effect_duration_ticks;
        }

        char GetFlags() const
        {
            return flags;
        }

#if PROTOCOL_VERSION > 758
        const std::optional<NBT::Value>& GetFactorData() const
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
            factor_data = ReadOptional<NBT::Value>(iter, length);
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
            WriteOptional<NBT::Value>(factor_data, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["entity_id"] = entity_id;
            output["effect_id"] = effect_id;
            output["effect_amplifier"] = effect_amplifier;
            output["effect_duration_ticks"] = effect_duration_ticks;
            output["flags"] = flags;
#if PROTOCOL_VERSION > 758
            if (factor_data.has_value())
            {
                output["factor_data"] = factor_data.value();
            }
#endif

            return output;
        }

    private:
        int entity_id = 0;
#if PROTOCOL_VERSION < 758
        char effect_id = 0;
#else
        int effect_id = 0;
#endif
        char effect_amplifier = 0;
        int effect_duration_ticks = 0;
        char flags = 0;
#if PROTOCOL_VERSION > 758
        std::optional<NBT::Value> factor_data;
#endif

    };
} //ProtocolCraft
