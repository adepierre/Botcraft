#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class SuspiciousStewEntry : public NetworkType
        {
        public:
            virtual ~SuspiciousStewEntry()
            {

            }

            int GetEffect() const
            {
                return effect;
            }

            int GetDuration() const
            {
                return duration;
            }


            void SetEffect(const int effect_)
            {
                effect = effect_;
            }

            void SetDuration(const int duration_)
            {
                duration = duration_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                effect = ReadData<VarInt>(iter, length);
                duration = ReadData<VarInt>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<VarInt>(effect, container);
                WriteData<VarInt>(duration, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["effect"] = effect;
                output["duration"] = duration;

                return output;
            }

        private:
            int effect = 0;
            int duration = 0;

        };
    }
}
#endif
