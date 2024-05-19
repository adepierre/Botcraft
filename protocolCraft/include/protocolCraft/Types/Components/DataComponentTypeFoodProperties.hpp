#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/PossibleEffect.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeFoodProperties : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeFoodProperties()
            {

            }


            int GetNutrition() const
            {
                return nutrition;
            }

            float GetSaturation() const
            {
                return saturation;
            }

            bool GetCanAlwaysEat() const
            {
                return can_always_eat;
            }

            float GetEatSeconds() const
            {
                return eat_seconds;
            }

            const std::vector<PossibleEffect>& GetEffects() const
            {
                return effects;
            }


            void SetNutrition(const int nutrition_)
            {
                nutrition = nutrition_;
            }

            void SetSaturation(const float saturation_)
            {
                saturation = saturation_;
            }

            void SetCanAlwaysEat(const bool can_always_eat_)
            {
                can_always_eat = can_always_eat_;
            }

            void SetEatSeconds(const float eat_seconds_)
            {
                eat_seconds = eat_seconds_;
            }

            void SetEffects(const std::vector<PossibleEffect>& effects_)
            {
                effects = effects_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                nutrition = ReadData<VarInt>(iter, length);
                saturation = ReadData<float>(iter, length);
                can_always_eat = ReadData<bool>(iter, length);
                eat_seconds = ReadData<float>(iter, length);
                effects = ReadData<std::vector<PossibleEffect>>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<VarInt>(nutrition, container);
                WriteData<float>(saturation, container);
                WriteData<bool>(can_always_eat, container);
                WriteData<float>(eat_seconds, container);
                WriteData<std::vector<PossibleEffect>>(effects, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["nutrition"] = nutrition;
                output["saturation"] = saturation;
                output["can_always_eat"] = can_always_eat;
                output["eat_seconds"] = eat_seconds;
                output["effects"] = effects;

                return output;
            }

        private:
            int nutrition = 0;
            float saturation = 0.0f;
            bool can_always_eat = false;
            float eat_seconds = 1.6f;
            std::vector<PossibleEffect> effects;

        };
    }
}
#endif
