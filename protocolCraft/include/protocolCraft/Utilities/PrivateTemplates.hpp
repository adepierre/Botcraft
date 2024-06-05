#pragma once

#include "protocolCraft/BinaryReadWrite.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Utilities/Json.hpp"
#include "protocolCraft/Utilities/Templates.hpp"

#include <memory>
#include <utility>

// All template functions that should only be used inside .cpp files

namespace ProtocolCraft
{
    // Template black magic to loop at compile time
    template<std::size_t... indices, class LoopBody>
    void loop_impl(std::index_sequence<indices...>, LoopBody&& loop_body) {
        (loop_body(std::integral_constant<std::size_t, indices>{}), ...);
    }

    template<std::size_t N, class LoopBody>
    void loop(LoopBody&& loop_body) {
        loop_impl(std::make_index_sequence<N>{}, std::forward<LoopBody>(loop_body));
    }

    /// @brief ReadData for each types in a tuple and store it in given ref
    /// @tparam FieldsTuple Tuple of types to read
    /// @param fields read data destination tuple
    /// @param iter read iterator
    /// @param length available data
    template <typename FieldsTuple>
    void ReadTuple(typename Internal::SerializedType<FieldsTuple>::storage_type& fields, ReadIterator& iter, size_t& length)
    {
        loop<std::tuple_size_v<FieldsTuple>>([&](auto i)
            {
                using NetworkElement = Internal::SerializedType<std::tuple_element_t<i, FieldsTuple>>;
                std::get<i>(fields) = ReadData<typename NetworkElement::storage_type, typename NetworkElement::serialization_type>(iter, length);
            }
        );
    }

    /// @brief WriteData for each types in a tuple
    /// @tparam FieldsTuple Tuple of types to write
    /// @param fields data source to write
    /// @param container write destination
    template <typename FieldsTuple>
    void WriteTuple(const typename Internal::SerializedType<FieldsTuple>::storage_type& fields, WriteContainer& container)
    {
        loop<std::tuple_size_v<FieldsTuple>>([&](auto i)
            {
                using NetworkElement = Internal::SerializedType<std::tuple_element_t<i, FieldsTuple>>;
                WriteData<typename NetworkElement::storage_type, typename NetworkElement::serialization_type>(std::get<i>(fields), container);
            }
        );
    }

    template<typename T>
    Json::Value SerializeType(std::conditional_t<std::is_arithmetic_v<T> || std::is_enum_v<T>, T, const T&> val)
    {
        if constexpr (Internal::IsOptional<T>)
        {
            if (val.has_value())
            {
                return SerializeType<typename T::value_type>(val.value());
            }
            else
            {
                return Json::Value();
            }
        }
        else if constexpr (Internal::IsMap<T>)
        {
            Json::Object map_object;
            for (const auto& [k, v] : val)
            {
                if constexpr (std::is_enum_v<typename T::key_type>)
                {
                    map_object[std::to_string(static_cast<std::underlying_type_t<typename T::key_type>>(k))] = SerializeType<typename T::mapped_type>(v);
                }
                else if constexpr (std::is_integral_v<typename T::key_type> && !std::is_same_v<typename T::key_type, bool>)
                {
                    map_object[std::to_string(k)] = SerializeType<typename T::mapped_type>(v);
                }
                else if constexpr (std::is_same_v<typename T::key_type, std::string>)
                {
                    map_object[k] = SerializeType<typename T::mapped_type>(v);
                }
                else if constexpr (std::is_same_v<typename T::key_type, Identifier>)
                {
                    map_object[k.GetFull()] = SerializeType<typename T::mapped_type>(v);
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
                return val;
            }
        }
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        else if constexpr (Internal::IsBitset<T>)
        {
            return val.to_string();
        }
#endif
        else if constexpr (Internal::IsPair<T>)
        {
            return {
                { "first",  val.first },
                { "second",  val.second }
            };
        }
        else
        {
            return val;
        }
    }

    /// @brief Serialize a tuple of data to a json value
    /// @tparam FieldsTuple Tuple of types to serialize
    /// @param fields data to serialize
    /// @param fields_names a name for each element in the tuple
    /// @return A Json representation of the tuple data
    template<typename FieldsTuple>
    Json::Value SerializeTuple(const typename Internal::SerializedType<FieldsTuple>::storage_type& fields, const std::array<std::string_view, std::tuple_size_v<FieldsTuple>>& fields_names)
    {
        Json::Value output;

        loop<std::tuple_size_v<FieldsTuple>>([&](auto i)
            {
                using CurrentElement = typename Internal::SerializedType<std::tuple_element_t<i, FieldsTuple>>::storage_type;
                if constexpr (Internal::IsOptional<CurrentElement>)
                {
                    if (std::get<i>(fields).has_value())
                    {
                        output[std::string(fields_names[i])] = std::get<i>(fields).value();
                    }
                }
                else
                {
                    output[std::string(fields_names[i])] = SerializeType<CurrentElement>(std::get<i>(fields));
                }
            }
        );

        return output;
    }
}
