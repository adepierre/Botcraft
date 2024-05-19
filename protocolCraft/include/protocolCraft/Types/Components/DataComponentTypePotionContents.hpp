#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/MobEffectInstance.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypePotionContents : public DataComponentType
        {
        public:
            virtual ~DataComponentTypePotionContents()
            {

            }


            const std::optional<int>& GetPotionId() const
            {
                return potion_id;
            }

            const std::optional<int>& GetCustomColor() const
            {
                return custom_color;
            }

            const std::vector<MobEffectInstance>& GetCustomEffects() const
            {
                return custom_effects;
            }


            void SetPotionId(const std::optional<int>& potion_id_)
            {
                potion_id = potion_id_;
            }

            void SetCustomColor(const std::optional<int>& custom_color_)
            {
                custom_color = custom_color_;
            }

            void SetCustomEffects(const std::vector<MobEffectInstance>& custom_effects_)
            {
                custom_effects = custom_effects_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                potion_id = ReadData<std::optional<VarInt>>(iter, length);
                custom_color = ReadData<std::optional<int>>(iter, length);
                custom_effects = ReadData<std::vector<MobEffectInstance>>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<std::optional<VarInt>>(potion_id, container);
                WriteData<std::optional<int>>(custom_color, container);
                WriteData<std::vector<MobEffectInstance>>(custom_effects, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                if (potion_id.has_value())
                {
                    output["potion_id"] = potion_id.value();
                }
                if (custom_color.has_value())
                {
                    output["custom_color"] = custom_color.value();
                }
                output["custom_effects"] = custom_effects;

                return output;
            }

        private:
            std::optional<int> potion_id;
            std::optional<int> custom_color;
            std::vector<MobEffectInstance> custom_effects;

        };
    }
}
#endif
