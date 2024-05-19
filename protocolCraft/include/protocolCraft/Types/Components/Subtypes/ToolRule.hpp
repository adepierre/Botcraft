#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/HolderSet.hpp"

#include <optional>
#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class ToolRule : public NetworkType
        {
        public:
            virtual ~ToolRule()
            {

            }


            const HolderSet& GetBlocks() const
            {
                return blocks;
            }

            const std::optional<float>& GetSpeed() const
            {
                return speed;
            }

            const std::optional<bool>& GetCorrectForDrop() const
            {
                return correct_for_drop;
            }


            void SetBlocks(const HolderSet& blocks_)
            {
                blocks = blocks_;
            }

            void SetSpeed(const std::optional<float>& speed_)
            {
                speed = speed_;
            }

            void SetCorrectForDrop(const std::optional<bool>& correct_for_drop_)
            {
                correct_for_drop = correct_for_drop_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                blocks = ReadData<HolderSet>(iter, length);
                speed = ReadData<std::optional<float>>(iter, length);
                correct_for_drop = ReadData<std::optional<bool>>(iter, length);

            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<HolderSet>(blocks, container);
                WriteData<std::optional<float>>(speed, container);
                WriteData<std::optional<bool>>(correct_for_drop, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["blocks"] = blocks;
                if (speed.has_value())
                {
                    output["speed"] = speed.value();
                }
                if (correct_for_drop.has_value())
                {
                    output["correct_for_drop"] = correct_for_drop.value();
                }

                return output;
            }

        private:
            HolderSet blocks;
            std::optional<float> speed;
            std::optional<bool> correct_for_drop;
        };
    }
}
#endif
