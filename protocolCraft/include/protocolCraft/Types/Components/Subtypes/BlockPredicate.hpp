#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"
#include "protocolCraft/Types/HolderSet.hpp"
#include "protocolCraft/Types/Components/Subtypes/StatePropertiesPredicate.hpp"

#include <optional>

namespace ProtocolCraft
{
    namespace Components
    {
        class BlockPredicate : public NetworkType
        {
        public:
            virtual ~BlockPredicate()
            {

            }


            const std::optional<HolderSet>& GetBlocks() const
            {
                return blocks;
            }

            const std::optional<StatePropertiesPredicate>& GetProperties() const
            {
                return properties;
            }

            const std::optional<NBT::Value>& GetNBT() const
            {
                return nbt;
            }


            void SetBlocks(const std::optional<HolderSet>& blocks_)
            {
                blocks = blocks_;
            }

            void SetProperties(const std::optional<StatePropertiesPredicate>& properties_)
            {
                properties = properties_;
            }

            void SetNBT(const std::optional<NBT::Value>& nbt_)
            {
                nbt = nbt_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                blocks = ReadData<std::optional<HolderSet>>(iter, length);
                properties = ReadData<std::optional<StatePropertiesPredicate>>(iter, length);
                nbt = ReadData<std::optional<NBT::Value>, std::optional<NBT::UnnamedValue>>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<std::optional<HolderSet>>(blocks, container);
                WriteData<std::optional<StatePropertiesPredicate>>(properties, container);
                WriteData<std::optional<NBT::Value>, std::optional<NBT::UnnamedValue>>(nbt, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                if (blocks.has_value())
                {
                    output["blocks"] = blocks.value();
                }
                if (properties.has_value())
                {
                    output["properties"] = properties.value();
                }
                if (nbt.has_value())
                {
                    output["nbt"] = nbt.value();
                }

                return output;
            }

        private:
            std::optional<HolderSet> blocks;
            std::optional<StatePropertiesPredicate> properties;
            std::optional<NBT::Value> nbt;

        };
    }
}
#endif
