#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/GlobalPos.hpp"

#include <optional>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeLodestoneTracker : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeLodestoneTracker()
            {

            }


            const std::optional<GlobalPos>& GetTarget() const
            {
                return target;
            }

            bool GetTracked() const
            {
                return tracked;
            }


            void SetTarget(const std::optional<GlobalPos>& target_)
            {
                target = target_;
            }

            void SetTracked(const bool tracked_)
            {
                tracked = tracked_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                target = ReadOptional<GlobalPos>(iter, length);
                tracked = ReadData<bool>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteOptional<GlobalPos>(target, container);
                WriteData<bool>(tracked, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                if (target.has_value())
                {
                    output["target"] = target.value();
                }
                output["tracked"] = tracked;

                return output;
            }

        private:
            std::optional<GlobalPos> target;
            bool tracked = true;

        };
    }
}
#endif
