#pragma once

#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Utilities/Json.hpp"
#include "protocolCraft/Utilities/Templates.hpp"

#include <utility>

namespace ProtocolCraft
{
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
    inline std::optional<Json::Value> WrapJsonWithOffsets(const std::optional<Json::Value>& v, const size_t* start_offset, const size_t* end_offset)
    {
        if (!v.has_value() || start_offset == nullptr || end_offset == nullptr)
        {
            return v;
        }

        return Json::Object({
            { "start_offset", *start_offset },
            { "end_offset", *end_offset },
            { "content", v.value() }
        });
    }
#endif

    template<typename T>
    std::optional<Json::Value> SerializeType(std::conditional_t<std::is_arithmetic_v<T> || std::is_enum_v<T>, T, const T&> val
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
        ,
        const typename Internal::OffsetType<T>::type* start_offset = nullptr,
        const typename Internal::OffsetType<T>::type* end_offset = nullptr
#endif
    )
    {
        if constexpr (Internal::IsOptional<T>)
        {
            if (val.has_value())
            {
                return SerializeType<typename T::value_type>(val.value()
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                    ,
                    start_offset,
                    end_offset
#endif
                );
            }
            else
            {
                return std::nullopt;
            }
        }
        else if constexpr (Internal::IsMap<T>)
        {
            Json::Object map_object;
            for (const auto& [k, v] : val)
            {
                const std::optional<Json::Value> serialized = SerializeType<typename T::mapped_type>(v
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                    ,
                    (start_offset != nullptr && start_offset->second.find(k) != start_offset->second.end()) ? &start_offset->second.at(k) : nullptr,
                    (end_offset != nullptr && end_offset->second.find(k) != end_offset->second.end()) ? &end_offset->second.at(k) : nullptr
#endif
                );
                if constexpr (std::is_enum_v<typename T::key_type>)
                {
                    map_object[std::to_string(static_cast<std::underlying_type_t<typename T::key_type>>(k))] = serialized.value_or(Json::Value());
                }
                else if constexpr (std::is_integral_v<typename T::key_type> && !std::is_same_v<typename T::key_type, bool>)
                {
                    map_object[std::to_string(k)] = serialized.value_or(Json::Value());
                }
                else if constexpr (std::is_same_v<typename T::key_type, std::string>)
                {
                    map_object[k] = serialized.value_or(Json::Value());
                }
                else if constexpr (std::is_same_v<typename T::key_type, Identifier>)
                {
                    map_object[k.GetFull()] = serialized.value_or(Json::Value());
                }
                else
                {
                    static_assert(Internal::dependant_false<T>, "Map key type not supported in auto JSON serialization");
                }
            }

#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            return WrapJsonWithOffsets(map_object, start_offset != nullptr ? &start_offset->first : nullptr, end_offset != nullptr ? &end_offset->first : nullptr);
#else
            return map_object;
#endif
        }
        else if constexpr (Internal::IsVector<T> || Internal::IsArray<T>)
        {
            if constexpr (std::is_same_v<typename T::value_type, char>)
            {
                if (val.size() > 16)
                {
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                    return WrapJsonWithOffsets("Vector of " + std::to_string(val.size()) + " chars", start_offset != nullptr ? &start_offset->first : nullptr, end_offset != nullptr ? &end_offset->first : nullptr);
#else
                    return "Vector of " + std::to_string(val.size()) + " chars";

#endif
                }
                else
                {
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                    return WrapJsonWithOffsets(val, start_offset != nullptr ? &start_offset->first : nullptr, end_offset != nullptr ? &end_offset->first : nullptr);
#else
                    return val;
#endif
                }
            }
            else if constexpr (std::is_same_v<typename T::value_type, unsigned char>)
            {
                if (val.size() > 16)
                {
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                    return WrapJsonWithOffsets("Vector of " + std::to_string(val.size()) + " unsigned chars", start_offset != nullptr ? &start_offset->first : nullptr, end_offset != nullptr ? &end_offset->first : nullptr);
#else
                    return "Vector of " + std::to_string(val.size()) + " unsigned chars";
#endif
                }
                else
                {
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                    return WrapJsonWithOffsets(val, start_offset != nullptr ? &start_offset->first : nullptr, end_offset != nullptr ? &end_offset->first : nullptr);
#else
                    return val;
#endif
                }
            }
            else
            {
                Json::Array output;
                output.reserve(val.size());
                for (size_t i = 0; i < val.size(); ++i)
                {
                    output.push_back(SerializeType<typename T::value_type>(val[i]
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                        ,
                        (start_offset != nullptr && start_offset->second.size() > i) ? &start_offset->second[i] : nullptr,
                        (end_offset != nullptr && end_offset->second.size() > i) ? &end_offset->second[i] : nullptr
#endif
                    ).value_or(Json::Value()));
                }
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                return WrapJsonWithOffsets(output, start_offset != nullptr ? &start_offset->first : nullptr, end_offset != nullptr ? &end_offset->first : nullptr);
#else
                return output;
#endif
            }
        }
        else if constexpr (Internal::IsBitset<T>)
        {
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            return WrapJsonWithOffsets(val.to_string(), start_offset, end_offset);
#else
            return val.to_string();
#endif
        }
        else if constexpr (Internal::IsPair<T>)
        {
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            return WrapJsonWithOffsets(Json::Value({
                { "first",  WrapJsonWithOffsets(val.first, start_offset != nullptr ? &start_offset->second.first : nullptr, end_offset != nullptr ? &end_offset->second.first : nullptr) },
                { "second",  WrapJsonWithOffsets(val.second, start_offset != nullptr ? &start_offset->second.second : nullptr, end_offset != nullptr ? &end_offset->second.second : nullptr) }
            }), start_offset != nullptr ? &start_offset->first, end_offset != nullptr ? &end_offset->first);
#else
            return Json::Value({
                { "first", val.first },
                { "second", val.second }
            });
#endif
        }
        else if constexpr (Internal::IsSharedPtr<T>)
        {
            if (val == nullptr)
            {
                return std::nullopt;
            }
            return SerializeType<typename T::element_type>(*val
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
                ,
                start_offset,
                end_offset
#endif
            );
        }
        else
        {
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
            return WrapJsonWithOffsets(val, start_offset, end_offset);
#else
            return val;
#endif
        }
    }
}
