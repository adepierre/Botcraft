#pragma once

#include <array>
#include <bitset>
#include <map>
#include <optional>
#include <tuple>
#include <utility>
#include <vector>

namespace ProtocolCraft
{
    namespace NBT
    {
        class Value;
        class UnnamedValue;
    }

    template <typename T>
    struct VarType { using underlying_type = T; };


    namespace Internal
    {
        /// @brief Concat multiple tuples in one big tuple
        /// @tparam ...input_t Multiple std::tuple types to concat
        template<typename ... input_t>
        using tuple_cat_t =
            decltype(std::tuple_cat(
                std::declval<input_t>()...
            ));

        template <typename T, typename Tuple> constexpr bool tuple_contains_type = false;
        template <typename T, typename... Ts> constexpr bool tuple_contains_type<T, std::tuple<Ts...>> = std::disjunction_v<std::is_same<T, Ts>...>;

        template <typename T, typename Tuple>                   constexpr int get_tuple_index                                = 0;
        template <typename T, typename... Rest>                 constexpr int get_tuple_index<T, std::tuple<T, Rest...>>     = 0;
        template <typename T, typename First, typename... Rest> constexpr int get_tuple_index<T, std::tuple<First, Rest...>> = 1 + get_tuple_index<T, std::tuple<Rest...>>;

        // Template black magic to loop at compile time
        template<std::size_t... indices, class LoopBody>
        void loop_impl(std::index_sequence<indices...>, LoopBody&& loop_body) {
            (loop_body(std::integral_constant<std::size_t, indices>{}), ...);
        }

        template<std::size_t N, class LoopBody>
        void loop(LoopBody&& loop_body) {
            loop_impl(std::make_index_sequence<N>{}, std::forward<LoopBody>(loop_body));
        }


        /// @brief Just a simple type wrapper that will store with T1 and serialize as T2 (can be used for Enum/VarInt for example)
        /// @tparam T1 Storage type
        /// @tparam T2 Serialization type
        template <typename T1, typename T2> struct DiffType {};

        template <typename T> struct GetClassFromConditionPtr;
        template <typename C> struct GetClassFromConditionPtr<bool(C::*)() const> { using Class = C; };

        /// @brief A type wrapper to conditionally serialize a type
        /// @tparam T Underlying type, can be VarType or DiffType too
        /// @tparam Condition A condition function pointer to a non static const class member function returning a bool, i.e. ``bool(*Class::Condition)(const Class*) const``
        /// @tparam StoredAsOptional If true, T will be stored as empty std::optional when Condition is not satisfied instead of default initialized values
        template <typename T, auto Condition, bool StoredAsOptional = true>
        struct Conditioned
        {
            using type = T;
            static constexpr bool stored_as_optional = StoredAsOptional;
            // Technically we could just store Condition and use it with (this->*Conditioned::Condition)() but that's a bit ugly
            // So instead we use this simpler tu use wrapper around it
            static bool Evaluate(const typename GetClassFromConditionPtr<decltype(Condition)>::Class* t)
            {
                return (t->*Condition)();
            }
        };

        template <typename T>                 constexpr bool IsArray                             = false;
        template <typename T, size_t N>       constexpr bool IsArray<std::array<T, N>>           = true;
        template <typename T>                 constexpr bool IsVector                            = false;
        template <typename T>                 constexpr bool IsVector<std::vector<T>>            = true;
        template <typename T>                 constexpr bool IsMap                               = false;
        template <typename K, typename V>     constexpr bool IsMap<std::map<K, V>>               = true;
        template <typename T>                 constexpr bool IsVarType                           = false;
        template <typename T>                 constexpr bool IsVarType<VarType<T>>               = true;
        template <typename T>                 constexpr bool IsOptional                          = false;
        template <typename T>                 constexpr bool IsOptional<std::optional<T>>        = true;
        template <typename T>                 constexpr bool IsPair                              = false;
        template <typename T1, typename T2>   constexpr bool IsPair<std::pair<T1, T2>>           = true;
        template <typename T>                 constexpr bool IsBitset                            = false;
        template <size_t N>                   constexpr bool IsBitset<std::bitset<N>>            = true;
        template <typename T>                 constexpr bool IsConditioned                       = false;
        template <typename T, auto C, bool b> constexpr bool IsConditioned<Conditioned<T, C, b>> = true;


        template <typename T>                 struct SerializedType                       { using storage_type = T;                                                                                                                        using serialization_type = T;                                                             };
        template <typename T>                 struct SerializedType<VarType<T>>           { using storage_type = typename VarType<T>::underlying_type;                                                                                     using serialization_type = VarType<T>;                                                    };
        template <>                           struct SerializedType<NBT::UnnamedValue>    { using storage_type = NBT::Value;                                                                                                               using serialization_type = NBT::UnnamedValue;                                             };
        template <typename T, size_t N>       struct SerializedType<std::array<T, N>>     { using storage_type = std::array<typename SerializedType<T>::storage_type, N>;                                                                  using serialization_type = std::array<T, N>;                                              };
        template <typename T>                 struct SerializedType<std::vector<T>>       { using storage_type = std::vector<typename SerializedType<T>::storage_type>;                                                                    using serialization_type = std::vector<T>;                                                };
        template <typename T>                 struct SerializedType<std::optional<T>>     { using storage_type = std::optional<typename SerializedType<T>::storage_type>;                                                                  using serialization_type = std::optional<T>;                                              };
        template <typename K, typename V>     struct SerializedType<std::map<K, V>>       { using storage_type = std::map<typename SerializedType<K>::storage_type, typename SerializedType<V>::storage_type>;                             using serialization_type = std::map<K, V>;                                                };
        template <typename T1, typename T2>   struct SerializedType<std::pair<T1, T2>>    { using storage_type = std::pair<typename SerializedType<T1>::storage_type, typename SerializedType<T2>::storage_type>;                          using serialization_type = std::pair<T1, T2>;                                             };
        template <typename T1, typename T2>   struct SerializedType<DiffType<T1, T2>>     { using storage_type = T1;                                                                                                                       using serialization_type = T2;                                                            };
        template <typename T, auto F, bool b> struct SerializedType<Conditioned<T, F, b>> { using storage_type = std::conditional_t<b, std::optional<typename SerializedType<T>::storage_type>, typename SerializedType<T>::storage_type>; using serialization_type = typename SerializedType<T>::serialization_type;                };
        template <typename ...P>              struct SerializedType<std::tuple<P...>>     { using storage_type = std::tuple<typename SerializedType<P>::storage_type...>;                                                                  using serialization_type = std::tuple<typename SerializedType<P>::serialization_type...>; };

        /// @brief To be used in constexpr else to fail compilation in a C++ compliant way
        /// @tparam T Any type
        template <typename T> constexpr bool dependant_false = false;
    }
}
