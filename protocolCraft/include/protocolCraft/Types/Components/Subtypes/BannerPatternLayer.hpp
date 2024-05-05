#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class BannerPatternLayer : public NetworkType
        {
        public:
            virtual ~BannerPatternLayer()
            {

            }


            int GetPattern() const
            {
                return pattern;
            }

            int GetColor() const
            {
                return color;
            }


            void SetPattern(const int pattern_)
            {
                pattern = pattern_;
            }

            void SetColor(const int color_)
            {
                color = color_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                pattern = ReadData<VarInt>(iter, length);
                color = ReadData<VarInt>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<VarInt>(pattern, container);
                WriteData<VarInt>(color, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["pattern"] = pattern;
                output["color"] = color;

                return output;
            }

        private:
            int pattern;
            int color;

        };
    }
}
#endif
