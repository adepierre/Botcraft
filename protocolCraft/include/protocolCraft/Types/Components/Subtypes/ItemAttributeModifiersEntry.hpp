#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Components/Subtypes/AttributeModifier.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class ItemAttributeModifiersEntry : public NetworkType
        {
        public:
            virtual ~ItemAttributeModifiersEntry()
            {

            }


            int GetAttribute() const
            {
                return attribute;
            }

            const AttributeModifier& GetModifier() const
            {
                return modifier;
            }

            int GetSlot() const
            {
                return slot;
            }


            void SetAttribute(const int attribute_)
            {
                attribute = attribute_;
            }

            void SetModifier(const AttributeModifier& modifier_)
            {
                modifier = modifier_;
            }

            void SetSlot(const int slot_)
            {
                slot = slot_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                attribute = ReadData<VarInt>(iter, length);
                modifier = ReadData<AttributeModifier>(iter, length);
                slot = ReadData<VarInt>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<VarInt>(attribute, container);
                WriteData<AttributeModifier>(modifier, container);
                WriteData<VarInt>(slot, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["attribute"] = attribute;
                output["modifier"] = modifier;
                output["slot"] = slot;

                return output;
            }

        private:
            int attribute = 0;
            AttributeModifier modifier;
            int slot = 0;

        };
    }
}
#endif
