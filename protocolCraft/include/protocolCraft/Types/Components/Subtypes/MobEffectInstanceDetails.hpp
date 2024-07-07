#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Utilities/CustomType.hpp"

#include <memory>

namespace ProtocolCraft
{
    namespace Components
    {
        class MobEffectInstanceDetails : public NetworkType
        {
        private:
            std::shared_ptr<MobEffectInstanceDetails> ReadHiddenEffect(ReadIterator& iter, size_t& length) const
            {
                std::shared_ptr<MobEffectInstanceDetails> hidden_effect = nullptr;
                if (ReadData<bool>(iter, length))
                {
                    hidden_effect = std::make_shared<MobEffectInstanceDetails>();
                    hidden_effect->Read(iter, length);
                }
                return hidden_effect;
            }

            void WriteHiddenEffect(const std::shared_ptr<MobEffectInstanceDetails>& hidden_effect, WriteContainer& container) const
            {
                WriteData<bool>(hidden_effect != nullptr, container);
                if (hidden_effect != nullptr)
                {
                    WriteData<MobEffectInstanceDetails>(*hidden_effect, container);
                }
            }

            DECLARE_FIELDS(
                (VarInt,    VarInt,   bool,    bool,          bool,     Internal::CustomType<std::shared_ptr<MobEffectInstanceDetails>, &MobEffectInstanceDetails::ReadHiddenEffect, &MobEffectInstanceDetails::WriteHiddenEffect>),
                (Amplifier, Duration, Ambient, ShowParticles, ShowIcon, HiddenEffect)
            );
            DECLARE_READ_WRITE_SERIALIZE;

            GETTER_SETTER(Amplifier);
            GETTER_SETTER(Duration);
            GETTER_SETTER(Ambient);
            GETTER_SETTER(ShowParticles);
            GETTER_SETTER(ShowIcon);
            GETTER_SETTER(HiddenEffect);
        };
    }
}
#endif
