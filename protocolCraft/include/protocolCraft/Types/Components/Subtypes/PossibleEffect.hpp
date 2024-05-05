#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Components/Subtypes/MobEffectInstance.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class PossibleEffect : public NetworkType
        {
        public:
            virtual ~PossibleEffect()
            {

            }


            const MobEffectInstance& GetEffect() const
            {
                return effect;
            }

            float GetProbability() const
            {
                return probability;
            }


            void SetEffect(const MobEffectInstance& effect_)
            {
                effect = effect_;
            }

            void SetProbability(const float probability_)
            {
                probability = probability_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                effect = ReadData<MobEffectInstance>(iter, length);
                probability = ReadData<float>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<MobEffectInstance>(effect, container);
                WriteData<float>(probability, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["effect"] = effect;
                output["probability"] = probability;

                return output;
            }

        private:
            MobEffectInstance effect;
            float probability = 1.0f;

        };
    }
}
#endif
