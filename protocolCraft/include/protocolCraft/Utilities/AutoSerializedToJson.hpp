#pragma once

#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Utilities/Json.hpp"
#include "protocolCraft/Utilities/Templates.hpp"

#include <utility>

namespace ProtocolCraft
{
    template<typename T>
    std::optional<Json::Value> SerializeType(std::conditional_t<std::is_arithmetic_v<T> || std::is_enum_v<T>, T, const T&> val)
    {
        if constexpr (Internal::IsOptional<T>)
        {
            if (val.has_value())
            {
                return SerializeType<typename T::value_type>(val.value());
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
                const std::optional<Json::Value> serialized = SerializeType<typename T::mapped_type>(v);
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
            return map_object;
        }
        else if constexpr (Internal::IsVector<T>)
        {
            if constexpr (std::is_same_v<typename T::value_type, char>)
            {
                if (val.size() > 16)
                {
                    return "Vector of " + std::to_string(val.size()) + " chars";
                }
                else
                {
                    return val;
                }
            }
            else if constexpr (std::is_same_v<typename T::value_type, unsigned char>)
            {
                if (val.size() > 16)
                {
                    return "Vector of " + std::to_string(val.size()) + " unsigned chars";
                }
                else
                {
                    return val;
                }
            }
            else
            {
                Json::Array output;
                output.reserve(val.size());
                for (const auto& v : val)
                {
                    output.push_back(SerializeType<typename T::value_type>(v).value_or(Json::Value()));
                }
                return output;
            }
        }
        else if constexpr (Internal::IsBitset<T>)
        {
            return val.to_string();
        }
        else if constexpr (Internal::IsPair<T>)
        {
            return Json::Value({
                { "first",  val.first },
                { "second",  val.second }
            });
        }
        else if constexpr (Internal::IsSharedPtr<T>)
        {
            if (val == nullptr)
            {
                return std::nullopt;
            }
            return SerializeType<typename T::element_type>(*val);
        }
        else
        {
            return val;
        }
    }
}
