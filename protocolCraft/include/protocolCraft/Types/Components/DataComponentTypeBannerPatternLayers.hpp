#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/BannerPatternLayer.hpp"

#include <vector>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeBannerPatternLayers : public DataComponentType
        {
        public:
            virtual ~DataComponentTypeBannerPatternLayers()
            {

            }


            const std::vector<BannerPatternLayer>& GetLayers() const
            {
                return layers;
            }


            void SetLayers(const std::vector<BannerPatternLayer>& layers_)
            {
                layers = layers_;
            }

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override
            {
                layers = ReadVector<BannerPatternLayer>(iter, length);
            }

            virtual void WriteImpl(WriteContainer& container) const override
            {
                WriteVector<BannerPatternLayer>(layers, container);
            }

            virtual Json::Value SerializeImpl() const override
            {
                Json::Value output;

                output["layers"] = layers;

                return output;
            }

        private:
            std::vector<BannerPatternLayer> layers;

        };
    }
}
#endif
