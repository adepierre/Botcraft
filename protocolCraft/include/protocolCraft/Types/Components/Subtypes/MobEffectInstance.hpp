#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Components/Subtypes/MobEffectInstanceDetails.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class MobEffectInstance : public NetworkType
        {
        public:
            virtual ~MobEffectInstance()
            {

            }


            int GetMobEffect() const
            {
                return mob_effect;
            }

            const MobEffectInstanceDetails& GetDetails() const
            {
                return details;
            }


            void SetMobEffect(const int mob_effect_)
            {
                mob_effect = mob_effect_;
            }

            void SetDetails(const MobEffectInstanceDetails& details_)
            {
                details = details_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                mob_effect = ReadData<VarInt>(iter, length);
                details = ReadData<MobEffectInstanceDetails>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<VarInt>(mob_effect, container);
                WriteData<MobEffectInstanceDetails>(details, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["mob_effect"] = mob_effect;
                output["details"] = details;

                return output;
            }

        private:
            int mob_effect = 0;
            MobEffectInstanceDetails details;

        };
    }
}
#endif
