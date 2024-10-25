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

            SERIALIZED_FIELD(Amplifier, VarInt);
            SERIALIZED_FIELD(Duration, VarInt);
            SERIALIZED_FIELD(Ambient, bool);
            SERIALIZED_FIELD(ShowParticles, bool);
            SERIALIZED_FIELD(ShowIcon, bool);
            SERIALIZED_FIELD(HiddenEffect, Internal::CustomType<std::shared_ptr<MobEffectInstanceDetails>, &MobEffectInstanceDetails::ReadHiddenEffect, &MobEffectInstanceDetails::WriteHiddenEffect>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
