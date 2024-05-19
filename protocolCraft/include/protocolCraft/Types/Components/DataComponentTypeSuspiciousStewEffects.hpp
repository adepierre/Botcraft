#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/SuspiciousStewEntry.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeSuspiciousStewEffects : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeSuspiciousStewEffects()
            {

            }


            const std::vector<SuspiciousStewEntry>& GetEffects() const
            {
                return effects;
            }


            void SetEffects(const std::vector<SuspiciousStewEntry>& effects_)
            {
                effects = effects_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                effects = ReadData<std::vector<SuspiciousStewEntry>>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<std::vector<SuspiciousStewEntry>>(effects, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["effects"] = effects;

                return output;
            }

        private:
            std::vector<SuspiciousStewEntry> effects;

        };
    }
}
#endif
