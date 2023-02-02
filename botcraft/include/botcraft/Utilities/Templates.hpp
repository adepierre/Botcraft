#pragma once

#include <type_traits>

// Generate two constexpr templated bools to check if
// a function is a member of a class.
// - has_name<Class, function> to check for simple name existence
// - has_name<Class, function, ret(args...)> to check for existence with signature constraint
#define GENERATE_CHECK_HAS_FUNC(FuncName) \
    template <typename, typename = void, typename = void> \
    constexpr bool has_##FuncName = false; \
    \
    template <typename T> \
    constexpr bool has_##FuncName<T, \
        typename std::enable_if_t<std::is_member_function_pointer_v<decltype(&T::FuncName)>>> \
    = true; \
    \
    template <typename T, typename Ret, typename... Args> \
    constexpr bool has_##FuncName<T, Ret(Args...), \
        std::void_t<decltype(std::declval<T>().FuncName(std::declval<Args>()...))>> \
    = std::is_same_v<decltype(std::declval<T>().FuncName(std::declval<Args>()...)), Ret>;
