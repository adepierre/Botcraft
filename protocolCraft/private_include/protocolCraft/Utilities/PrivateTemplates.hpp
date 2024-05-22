#pragma once

#include "protocolCraft/BinaryReadWrite.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Utilities/Json.hpp"
#include "protocolCraft/Utilities/Templates.hpp"

#include <memory>
#include <utility>

namespace ProtocolCraft
{
    struct PrivateFieldsAccessor
    {
        template <typename T> static constexpr int num_fields = static_cast<int>(T::FieldsEnum::NUM_FIELDS);
        template <typename T> static constexpr std::string_view raw_names = T::raw_names;
    };

    // Template black magic to loop at compile time
    template<std::size_t... indices, class LoopBody>
    void loop_impl(std::index_sequence<indices...>, LoopBody&& loop_body) {
        (loop_body(std::integral_constant<std::size_t, indices>{}), ...);
    }

    template<std::size_t N, class LoopBody>
    void loop(LoopBody&& loop_body) {
        loop_impl(std::make_index_sequence<N>{}, std::forward<LoopBody>(loop_body));
    }

    class Message;
    template<typename TypesTuple>
    std::shared_ptr<ProtocolCraft::Message> AutomaticMessageFactory(const int id)
    {
        std::shared_ptr<ProtocolCraft::Message> output = nullptr;

        loop<std::tuple_size<TypesTuple>{}> (
            [&](auto i)
            {
                using TupleElement = std::tuple_element_t<i, TypesTuple>;
                if (id == TupleElement::packet_id)
                {
                    output = std::make_shared<TupleElement>();
                }
            }
        );

        return output;
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
                else if constexpr (Internal::IsMap<CurrentElement>)
                {
                    Json::Object map_object;
                    for (const auto& [k, v] : std::get<i>(fields))
                    {
                        if constexpr (std::is_enum_v<typename CurrentElement::key_type>)
                        {
                            map_object[std::to_string(static_cast<std::underlying_type_t<typename CurrentElement::key_type>>(k))] = v;
                        }
                        else if constexpr (std::is_integral_v<typename CurrentElement::key_type> && !std::is_same_v<typename CurrentElement::key_type, bool>)
                        {
                            map_object[std::to_string(k)] = v;
                        }
                        else if constexpr (std::is_same_v<typename CurrentElement::key_type, std::string>)
                        {
                            map_object[k] = v;
                        }
                        else if constexpr (std::is_same_v <typename CurrentElement::key_type, Identifier>)
                        {
                            map_object[k.GetFull()] = v;
                        }
                        else
                        {
                            static_assert(Internal::dependant_false<CurrentElement>, "Map key type not supported in auto JSON serialization");
                        }
                    }
                    output[std::string(fields_names[i])] = map_object;
                }
                else if constexpr (Internal::IsVector<CurrentElement>)
                {
                    if constexpr (std::is_same_v<typename CurrentElement::value_type, char>)
                    {
                        if (std::get<i>(fields).size().size() > 10)
                        {
                            output[std::string(fields_names[i])] = "Vector of " + std::to_string(std::get<i>(fields).size()) + " chars";
                        }
                        else
                        {
                            output[std::string(fields_names[i])] = std::get<i>(fields);
                        }
                    }
                    else if constexpr (std::is_same_v<typename CurrentElement::value_type, unsigned char>)
                    {
                        if (std::get<i>(fields).size().size() > 10)
                        {
                            output[std::string(fields_names[i])] = "Vector of " + std::to_string(std::get<i>(fields).size()) + " unsigned chars";
                        }
                        else
                        {
                            output[std::string(fields_names[i])] = std::get<i>(fields);
                        }
                    }
                    else
                    {
                        output[std::string(fields_names[i])] = std::get<i>(fields);
                    }
                }
                else
                {
                    output[std::string(fields_names[i])] = std::get<i>(fields);
                }
            }
        );

        return output;
    }
}
