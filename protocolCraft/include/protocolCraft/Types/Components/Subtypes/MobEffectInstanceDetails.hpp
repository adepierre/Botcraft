#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/NetworkType.hpp"

#include <memory>

namespace ProtocolCraft
{
    namespace Components
    {
        class MobEffectInstanceDetails : public NetworkType
        {
        public:
            virtual ~MobEffectInstanceDetails()
            {

            }


            int GetAmplifier() const
            {
                return amplifier;
            }

            int GetDuration() const
            {
                return duration;
            }

            bool GetAmbient() const
            {
                return ambient;
            }

            bool GetShowParticles() const
            {
                return show_particles;
            }

            bool GetShowIcon() const
            {
                return show_icon;
            }

            std::shared_ptr<MobEffectInstanceDetails> GetHiddenEffect() const
            {
                return hidden_effect;
            }


            void SetAmplifier(const int amplifier_)
            {
                amplifier = amplifier_;
            }

            void SetDuration(const int duration_)
            {
                duration = duration_;
            }

            void SetAmbient(const bool ambient_)
            {
                ambient = ambient_;
            }

            void SetShowParticles(const bool show_particles_)
            {
                show_particles = show_particles_;
            }

            void SetShowIcon(const bool show_icon_)
            {
                show_icon = show_icon_;
            }

            void SetHiddenEffect(const std::shared_ptr<MobEffectInstanceDetails>& hidden_effect_)
            {
                hidden_effect = hidden_effect_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                amplifier = ReadData<VarInt>(iter, length);
                duration = ReadData<VarInt>(iter, length);
                ambient = ReadData<bool>(iter, length);
                show_particles = ReadData<bool>(iter, length);
                show_icon = ReadData<bool>(iter, length);
                // Pointer std::optional
                if (ReadData<bool>(iter, length))
                {
                    hidden_effect = std::make_shared<MobEffectInstanceDetails>();
                    hidden_effect->Read(iter, length);
                }
                else
                {
                    hidden_effect = nullptr;
                }
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<VarInt>(amplifier, container);
                WriteData<VarInt>(duration, container);
                WriteData<bool>(ambient, container);
                WriteData<bool>(show_particles, container);
                WriteData<bool>(show_icon, container);
                // Pointer std::optional
                WriteData<bool>(hidden_effect != nullptr, container);
                if (hidden_effect != nullptr)
                {
                    WriteData<MobEffectInstanceDetails>(*hidden_effect, container);
                }
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["amplifier"] = amplifier;
                output["duration"] = duration;
                output["ambient"] = ambient;
                output["show_particles"] = show_particles;
                output["show_icon"] = show_icon;
                if (hidden_effect != nullptr)
                {
                    output["hidden_effect"] = *hidden_effect;
                }

                return output;
            }

        private:
            int amplifier = 0;
            int duration = 0;
            bool ambient = false;
            bool show_particles = true;
            bool show_icon = false;
            // Sadly we need a pointer here to break the class recursion, so we'll use it as a cheap std::optional
            std::shared_ptr<MobEffectInstanceDetails> hidden_effect;

        };
    }
}
#endif
