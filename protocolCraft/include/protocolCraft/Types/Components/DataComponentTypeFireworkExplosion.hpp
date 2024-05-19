#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeFireworkExplosion : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeFireworkExplosion()
            {

            }


            int GetShape() const
            {
                return shape;
            }

            const std::vector<int>& GetColors() const
            {
                return colors;
            }

            const std::vector<int>& GetFadeColors() const
            {
                return fade_colors;
            }

            bool GetHasTrail() const
            {
                return has_trail;
            }

            bool GetHasTwinkle() const
            {
                return has_twinkle;
            }


            void SetShape(const int shape_)
            {
                shape = shape_;
            }

            void SetColors(const std::vector<int>& colors_)
            {
                colors = colors_;
            }

            void SetFadeColors(const std::vector<int>& fade_colors_)
            {
                fade_colors = fade_colors_;
            }

            void SetHasTrail(const bool has_trail_)
            {
                has_trail = has_trail_;
            }

            void SetHasTwinkle(const bool has_twinkle_)
            {
                has_twinkle = has_twinkle_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                shape = ReadData<int>(iter, length);
                colors = ReadData<std::vector<int>>(iter, length);
                fade_colors = ReadData<std::vector<int>>(iter, length);
                has_trail = ReadData<bool>(iter, length);
                has_twinkle = ReadData<bool>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteData<int>(shape, container);
                WriteData<std::vector<int>>(colors, container);
                WriteData<std::vector<int>>(fade_colors, container);
                WriteData<bool>(has_trail, container);
                WriteData<bool>(has_twinkle, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["shape"] = shape;
                output["colors"] = colors;
                output["fade_colors"] = fade_colors;
                output["has_trail"] = has_trail;
                output["has_twinkle"] = has_twinkle;

                return output;
            }

        private:
            int shape = 0;
            std::vector<int> colors;
            std::vector<int> fade_colors;
            bool has_trail = 0;
            bool has_twinkle = 0;

        };
    }
}
#endif
