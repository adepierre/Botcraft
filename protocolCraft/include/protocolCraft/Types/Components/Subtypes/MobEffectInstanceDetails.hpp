#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

#include <memory>

namespace ProtocolCraft
{
    namespace Components
    {
        class MobEffectInstanceDetails : public NetworkType
        {
            DECLARE_FIELDS_TYPES(VarInt,    VarInt,   bool,    bool,          bool,     std::shared_ptr<MobEffectInstanceDetails>);
            DECLARE_FIELDS_NAMES(Amplifier, Duration, Ambient, ShowParticles, ShowIcon, HiddenEffect);

            GETTER_SETTER(Amplifier);
            GETTER_SETTER(Duration);
            GETTER_SETTER(Ambient);
            GETTER_SETTER(ShowParticles);
            GETTER_SETTER(ShowIcon);
            GETTER_SETTER(HiddenEffect);

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                SetAmplifier(ReadData<VarInt>(iter, length));
                SetDuration(ReadData<VarInt>(iter, length));
                SetAmbient(ReadData<bool>(iter, length));
                SetShowParticles(ReadData<bool>(iter, length));
                SetShowIcon(ReadData<bool>(iter, length));
                // Pointer std::optional
                std::shared_ptr<MobEffectInstanceDetails> hidden_effect = nullptr;
                if (ReadData<bool>(iter, length))
                {
                    std::shared_ptr<MobEffectInstanceDetails> hidden_effect = std::make_shared<MobEffectInstanceDetails>();
                    hidden_effect->Read(iter, length);
                }
                SetHiddenEffect(hidden_effect);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<VarInt>(GetAmplifier(), container);
                WriteData<VarInt>(GetDuration(), container);
                WriteData<bool>(GetAmbient(), container);
                WriteData<bool>(GetShowParticles(), container);
                WriteData<bool>(GetShowIcon(), container);
                // Pointer std::optional
                WriteData<bool>(GetHiddenEffect() != nullptr, container);
                if (GetHiddenEffect() != nullptr)
                {
                    WriteData<MobEffectInstanceDetails>(*GetHiddenEffect(), container);
                }
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Amplifier)])] = GetAmplifier();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Duration)])] = GetDuration();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Ambient)])] = GetAmbient();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::ShowParticles)])] = GetShowParticles();
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::ShowIcon)])] = GetShowIcon();
                if (GetHiddenEffect() != nullptr)
                {
                    output[std::string(json_names[static_cast<size_t>(FieldsEnum::HiddenEffect)])] = *GetHiddenEffect();
                }

                return output;
            }
        };
    }
}
#endif
