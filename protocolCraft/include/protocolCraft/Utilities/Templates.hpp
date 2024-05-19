#pragma once

#include <array>
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include <bitset>
#endif
#include <map>
#include <optional>
#include <tuple>
#include <utility>
#include <vector>

namespace ProtocolCraft
{
    template <typename T>
    struct VarType { using underlying_type = T; };

    template <typename T1, typename T2> struct DiffType {};

    namespace Internal
    {
        // Concat multiple tuples in one big tuple
        template<typename ... input_t>
        using tuple_cat_t =
            decltype(std::tuple_cat(
                std::declval<input_t>()...
            ));

        template <typename T> constexpr bool IsArray = false;
        template <typename T, size_t N> constexpr bool IsArray<std::array<T, N>> = true;
        template <typename T> constexpr bool IsVector = false;
        template <typename T> constexpr bool IsVector<std::vector<T>> = true;
        template <typename T> constexpr bool IsMap = false;
        template <typename K, typename V> constexpr bool IsMap<std::map<K, V>> = true;
        template <typename T> constexpr bool IsVarType = false;
        template <typename T> constexpr bool IsVarType<VarType<T>> = true;
        template <typename T> constexpr bool IsOptional = false;
        template <typename T> constexpr bool IsOptional<std::optional<T>> = true;
        template <typename T> constexpr bool IsPair = false;
        template <typename T1, typename T2> constexpr bool IsPair<std::pair<T1, T2>> = true;
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        template <typename T> constexpr bool IsBitset = false;
        template <size_t N> constexpr bool IsBitset<std::bitset<N>> = true;
#endif
        template <typename T> struct NetworkType { using storage_type = T; using serialization_type = T; };
        template <typename T> struct NetworkType<VarType<T>> { using storage_type = typename VarType<T>::underlying_type; using serialization_type = VarType<T>; };
        template <typename T, size_t N> struct NetworkType<std::array<T, N>> { using storage_type = std::array<typename NetworkType<T>::storage_type, N>; using serialization_type = std::array<T, N>; };
        template <typename T> struct NetworkType<std::vector<T>> { using storage_type = std::vector<typename NetworkType<T>::storage_type>; using serialization_type = std::vector<T>; };
        template <typename T> struct NetworkType<std::optional<T>> { using storage_type = std::optional<typename NetworkType<T>::storage_type>; using serialization_type = std::optional<T>; };
        template <typename K, typename V> struct NetworkType<std::map<K, V>> { using storage_type = std::map<typename NetworkType<K>::storage_type, typename NetworkType<V>::storage_type>; using serialization_type = std::map<K, V>; };
        template <typename T1, typename T2> struct NetworkType<std::pair<T1, T2>> { using storage_type = std::pair<typename NetworkType<T1>::storage_type, typename NetworkType<T2>::storage_type>; using serialization_type = std::pair<T1, T2>; };
        template <typename T1, typename T2> struct NetworkType<DiffType<T1, T2>> { using storage_type = T1; using serialization_type = T2; };
        template <typename ...P> struct NetworkType<std::tuple<P...>> { using storage_type = std::tuple<typename NetworkType<P>::storage_type...>; using serialization_type = std::tuple<typename NetworkType<P>::serialization_type...>; };

        /// @brief To be used in constexpr else to fail compilation in a C++ compliant way
        /// @tparam T Any type
        template <typename T> constexpr bool dependant_false = false;
    }
}
