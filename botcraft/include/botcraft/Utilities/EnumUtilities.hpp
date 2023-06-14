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

        // Extract value from macros, with a -1 on the size cause we don't need the last \0 in a string_view
#if defined(__clang__)// "auto enum_value_name() [V = XXXXXX::XXXXX::XXXXX]"
        constexpr std::string_view header = "auto Botcraft::enum_value_name() [V = ";
        constexpr std::string_view footer = "]";
        return std::string_view{ __PRETTY_FUNCTION__ + header.size(), sizeof(__PRETTY_FUNCTION__) - 1 - header.size() - footer.size() };
#elif defined(__GNUC__)// "constexpr auto enum_value_name() [with auto V = XXXXXX::XXXXX::XXXXX]"
        constexpr std::string_view header = "constexpr auto Botcraft::enum_value_name() [with auto V = ";
        constexpr std::string_view footer = "]";
        return std::string_view{ __PRETTY_FUNCTION__ + header.size(), sizeof(__PRETTY_FUNCTION__) - 1 - header.size() - footer.size() };
#elif defined(_MSC_VER) // "auto __cdecl enum_value_name<XXXXXX::XXXXX::XXXXX>(void) noexcept"
        constexpr std::string_view header = "auto __cdecl Botcraft::enum_value_name<";
        constexpr std::string_view footer = ">(void) noexcept";
        return std::string_view{ __FUNCSIG__ + header.size(), sizeof(__FUNCSIG__) - 1 - header.size() - footer.size() };
#else
        static_assert(false, "enum_value_name requires either __PRETTY_FUNCTION__ or __FUNCSIG__ to be available");
#endif
    }

    template <class F, class T, T ... Is>
    constexpr void constexpr_for(F&& f, std::integer_sequence<T, Is...> const&)
    {
        ((f(std::integral_constant<T, Is>())), ...);
    }

    template<class Enum, Enum m, Enum M>
    struct EnumMapperRange
    {
        static_assert(static_cast<std::underlying_type_t<Enum>>(M) >= static_cast<std::underlying_type_t<Enum>>(m), "M must be >= m");

        constexpr EnumMapperRange() : mapping(), start(static_cast<std::underlying_type_t<Enum>>(m)), end(static_cast<std::underlying_type_t<Enum>>(M))
        {
            // Same as a for loop, but with constexpr friendly i
            //for (auto i = 0; i < end - start + 1; ++i)
            //{
            //    mapping[i] = enum_value_name<static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(m) + i)>();
            //}
            constexpr_for([this](auto i)
                {
                    mapping[i] = enum_value_name<static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(m) + i)>();
                }, std::make_integer_sequence<std::underlying_type_t<Enum>, static_cast<std::underlying_type_t<Enum>>(M) - static_cast<std::underlying_type_t<Enum>>(m) + 1>{});
        }

        std::array<std::string_view, static_cast<std::underlying_type_t<Enum>>(M) - static_cast<std::underlying_type_t<Enum>>(m) + 1> mapping;
        const std::underlying_type_t<Enum> start;
        const std::underlying_type_t<Enum> end;
    };

    template<class Enum, Enum... pack>
    constexpr std::array<std::pair<Enum, std::string_view>, sizeof...(pack)> GetNamedEnum()
    {
        return { std::make_pair(pack, enum_value_name<pack>())... };
    }
}

#define DECLARE_ENUM_STRINGIFYER(Enum) std::ostream& operator <<(std::ostream& os, const Enum v)


#if defined(__clang__) || defined(__GNUC__) || defined(_MSC_VER)
/// @brief Define << operator for Enum with string values between min_value and max_value (included)
#define DEFINE_ENUM_STRINGIFYER_RANGE(Enum, min_value, max_value)                                   \
std::ostream& operator <<(std::ostream& os, const Enum v)                                           \
{                                                                                                   \
    static_assert(std::is_same_v<decltype(min_value), Enum>, "min_value must be "#Enum);            \
    static_assert(std::is_same_v<decltype(max_value), Enum>, "max_value must be "#Enum);            \
    static constexpr auto mapper = Botcraft::EnumMapperRange<Enum, min_value, max_value>();         \
    if (static_cast<std::underlying_type_t<Enum>>(v) < mapper.start ||                              \
        static_cast<std::underlying_type_t<Enum>>(v) > mapper.end)                                  \
    {                                                                                               \
        return os << '(' << #Enum << ')' << static_cast<int>(v);                                    \
    }                                                                                               \
    return os << mapper.mapping[static_cast<std::underlying_type_t<Enum>>(v) - mapper.start];       \
} static_assert(true, "") /* To require a ; after macro call */
#else // min_value and max_value are not necessary, but keep them to get the same interface
#define DEFINE_ENUM_STRINGIFYER_RANGE(Enum, min_value, max_value)    \
std::ostream& operator <<(std::ostream& os, const Enum v)            \
{                                                                    \
    return os << '(' << #Enum << ')' << static_cast<int>(v);         \
} static_assert(true, "") /* To require a ; after macro call */
#endif

#if defined(__clang__) || defined(__GNUC__) || defined(_MSC_VER)
/// @brief Define << operator for Enum with string values for each value in ...
#define DEFINE_ENUM_STRINGIFYER_LIST(Enum, ...)                                         \
std::ostream& operator <<(std::ostream& os, const Enum v)                               \
{                                                                                       \
    static constexpr auto mapper = Botcraft::GetNamedEnum<Enum, __VA_ARGS__>();         \
    const auto it = std::find_if(mapper.begin(), mapper.end(),                          \
        [v](const std::pair<Enum, std::string_view>& p) { return p.first == v; });      \
    if (it == mapper.end())                                                             \
    {                                                                                   \
        return os << '(' << #Enum << ')' << static_cast<int>(v);                        \
    }                                                                                   \
    return os << it->second;                                                            \
} static_assert(true, "") /* To require a ; after macro call */
#else // value list is not necessary, but keep it to get the same interface
#define DEFINE_ENUM_STRINGIFYER_LIST(Enum, ...)                      \
std::ostream& operator <<(std::ostream& os, const Enum v)            \
{                                                                    \
    return os << '(' << #Enum << ')' << static_cast<int>(v);         \
} static_assert(true, "") /* To require a ; after macro call */
#endif
