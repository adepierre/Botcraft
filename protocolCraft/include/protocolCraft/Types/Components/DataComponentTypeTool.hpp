#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/ToolRule.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeTool : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeTool()
            {

            }


            const std::vector<ToolRule>& GetRules() const
            {
                return rules;
            }

            float GetDefaultMiningSpeed() const
            {
                return default_mining_speed;
            }

            int GetDamagePerBlock() const
            {
                return damage_per_block;
            }


            void SetRules(const std::vector<ToolRule>& rules_)
            {
                rules = rules_;
            }

            void SetDefaultMiningSpeed(const float default_mining_speed_)
            {
                default_mining_speed = default_mining_speed_;
            }

            void SetDamagePerBlock(const int damage_per_block_)
            {
                damage_per_block = damage_per_block_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                rules = ReadVector<ToolRule>(iter, length);
                default_mining_speed = ReadData<float>(iter, length);
                damage_per_block = ReadData<VarInt>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteVector<ToolRule>(rules, container);
                WriteData<float>(default_mining_speed, container);
                WriteData<VarInt>(damage_per_block, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["rules"] = rules;
                output["default_mining_speed"] = default_mining_speed;
                output["damage_per_block"] = damage_per_block;

                return output;
            }

        private:
            std::vector<ToolRule> rules;
            float default_mining_speed = 1.0f;
            int damage_per_block = 1;

        };
    }
}
#endif
