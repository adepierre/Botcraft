#pragma once

#include "protocolCraft/Utilities/Json.hpp"
#include "protocolCraft/Utilities/Templates.hpp"
#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"
#include "protocolCraft/BinaryReadWrite.hpp"

#include <memory>

namespace ProtocolCraft
{
    namespace Internal
    {
        /// @brief A dynamic field that can hold different data inheriting a common BaseType (derived from NetworkType). Cannot be used inside a container like a vector
        /// @tparam BaseType Common base class of every possible data type
        /// @tparam TypeField Pointer to the type field (e.g. &MyNetworkClass::Type)
        /// @tparam Factory Function pointer. Should have a signature std::shared_ptr<Base>(TypeValue)
        template <typename BaseType, auto TypeField, auto Factory>
        struct DynamicType
        {
            template <typename C>
            static std::shared_ptr<BaseType> Read(
                const C* c,
                std::vector<unsigned char>::const_iterator& iter,
                size_t& length
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                ,
                typename OffsetType<std::shared_ptr<BaseType>>::type* start_offset = nullptr,
                typename OffsetType<std::shared_ptr<BaseType>>::type* end_offset = nullptr
#endif
            )
            {

#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                if (start_offset != nullptr)
                {
                    *start_offset = length;
                }
#endif
                std::shared_ptr<BaseType> data = Factory(c->*TypeField);
                if (data != nullptr)
                {
                    data->Read(iter, length);
                }
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                if (end_offset != nullptr)
                {
                    *end_offset = length;
                }
#endif
                return data;
            }

            template <typename C>
            static void Write(const C* c, const std::shared_ptr<BaseType>& val, std::vector<unsigned char>& container)
            {
                if (val != nullptr)
                {
                    val->Write(container);
                }
            }

            template <typename C>
            static std::optional<Json::Value> Serialize(
                const C* c,
                const std::shared_ptr<BaseType>& val
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                ,
                const typename OffsetType<std::shared_ptr<BaseType>>::type* start_offset = nullptr,
                const typename OffsetType<std::shared_ptr<BaseType>>::type* end_offset = nullptr
#endif
            )
            {
                return SerializeType<std::shared_ptr<BaseType>>(val
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                    , start_offset, end_offset
#endif
                );
            }
        };
    }
}
