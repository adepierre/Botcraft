#pragma once

#include <type_traits>
#include <string_view>
#include <array>
#include <utility>
#include <algorithm>
#include <iostream>

namespace Botcraft
{
    template <auto V>
    constexpr auto enum_value_name() noexcept
    {
        static_assert(std::is_enum_v<decltype(V)>, "enum_value_name requires enum value");

#if defined(__clang__)
        constexpr std::string_view header = "auto Botcraft::enum_value_name() [V = ";
        constexpr std::string_view footer = "]";
        constexpr std::string_view name = __PRETTY_FUNCTION__;
#elif defined(__GNUC__)
        constexpr std::string_view header = "constexpr auto Botcraft::enum_value_name() [with auto V = ";
        constexpr std::string_view footer = "]";
        constexpr std::string_view name = __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
        constexpr std::string_view header = "auto __cdecl Botcraft::enum_value_name<";
        constexpr std::string_view footer = ">(void) noexcept";
        constexpr std::string_view name = __FUNCSIG__;
#else
        // V == V makes the assertion evaluated only if the function is instantiated
        static_assert(V == V && false, "enum_value_name requires either __PRETTY_FUNCTION__ or __FUNCSIG__ to be available");
#endif
        return name.substr(header.size(), name.size() - header.size() - footer.size());
    }

    template <class Enum>
    constexpr std::underlying_type_t<Enum> to_underlying(const Enum e) noexcept
    {
        return static_cast<std::underlying_type_t<Enum>>(e);
    }

    template<class Enum, Enum MinVal, Enum MaxVal>
    struct EnumMapperRange
    {
        static_assert(to_underlying(MaxVal) >= to_underlying(MinVal), "MaxVal must be >= MinVal");

        static inline constexpr std::underlying_type_t<Enum> start = to_underlying(MinVal);
        static inline constexpr std::underlying_type_t<Enum> end = to_underlying(MaxVal);

        template <std::size_t ... Is>
        static constexpr std::array<std::string_view, end - start + 1> map_range(std::index_sequence<Is...>)
        {
            std::array<std::string_view, end - start + 1> output;
            ((output[Is] = enum_value_name<static_cast<Enum>(start + Is)>()), ...);
            return output;
        }

        static inline constexpr std::array<std::string_view, end - start + 1> mapping = map_range(std::make_index_sequence<end - start + 1>());
    };

    template<class Enum, Enum... pack>
    constexpr std::array<std::pair<Enum, std::string_view>, sizeof...(pack)> GetNamedEnum()
    {
        return { std::make_pair(pack, enum_value_name<pack>())... };
    }
}

#define DECLARE_ENUM_STRINGIFYER(Enum) ::std::ostream& operator <<(::std::ostream& os, const Enum v)


#if defined(__clang__) || defined(__GNUC__) || defined(_MSC_VER)
#define DEFINE_ENUM_STRINGIFYER_RANGE(Enum, min_value, max_value)                          \
::std::ostream& operator <<(::std::ostream& os, const Enum v)                              \
{                                                                                          \
    static_assert(::std::is_same_v<decltype(min_value), Enum>, "min_value must be "#Enum); \
    static_assert(::std::is_same_v<decltype(max_value), Enum>, "max_value must be "#Enum); \
    using mapper = ::Botcraft::EnumMapperRange<Enum, min_value, max_value>;        \
    if (::Botcraft::to_underlying(v) < mapper::start ||                            \
        ::Botcraft::to_underlying(v) > mapper::end)                                \
    {                                                                                      \
        return os << '(' << #Enum << ')' << static_cast<int>(v);                           \
    }                                                                                      \
    return os << mapper::mapping[::Botcraft::to_underlying(v) - mapper::start];    \
} static_assert(true, "") /* To require a ; after macro call */
#else // min_value and max_value are not necessary, but keep them to get the same interface
#define DEFINE_ENUM_STRINGIFYER_RANGE(Enum, min_value, max_value)    \
::std::ostream& operator <<(::std::ostream& os, const Enum v)        \
{                                                                    \
    return os << '(' << #Enum << ')' << static_cast<int>(v);         \
} static_assert(true, "") /* To require a ; after macro call */
#endif

#if defined(__clang__) || defined(__GNUC__) || defined(_MSC_VER)
#define DEFINE_ENUM_STRINGIFYER_LIST(Enum, ...)                                           \
::std::ostream& operator <<(::std::ostream& os, const Enum v)                             \
{                                                                                         \
    static constexpr auto mapper = ::Botcraft::GetNamedEnum<Enum, __VA_ARGS__>();         \
    const auto it = ::std::find_if(mapper.begin(), mapper.end(),                          \
        [v](const ::std::pair<Enum, ::std::string_view>& p) { return p.first == v; });    \
    if (it == mapper.end())                                                               \
    {                                                                                     \
        return os << '(' << #Enum << ')' << static_cast<int>(v);                          \
    }                                                                                     \
    return os << it->second;                                                              \
} static_assert(true, "") /* To require a ; after macro call */
#else // value list is not necessary, but keep it to get the same interface
#define DEFINE_ENUM_STRINGIFYER_LIST(Enum, ...)   \
::std::ostream& operator <<(::std::ostream& os, const Enum v)        \
{                                                                    \
    return os << '(' << #Enum << ')' << static_cast<int>(v);         \
} static_assert(true, "") /* To require a ; after macro call */
#endif
