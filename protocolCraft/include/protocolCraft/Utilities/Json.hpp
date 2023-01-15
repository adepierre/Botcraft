#pragma once

#include <cassert>
#include <map>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>
#include <array>

#include "protocolCraft/Utilities/RecursiveWrapper.hpp"

namespace ProtocolCraft
{
    class NetworkType;

    namespace Json
    {
        // Forward declaration
        class Array;
        class Object;

        namespace Internal
        {
            /// @brief std::variant holding the actual data
            using JsonVariant = std::variant<
                std::monostate,
                ProtocolCraft::Internal::RecursiveWrapper<Object>,
                ProtocolCraft::Internal::RecursiveWrapper<Array>,
                std::string,
                bool,
                long long int,
                unsigned long long int,
                double
            >;
        }


        /// @brief Main class, basically a JsonVariant with extra utility functions
        /// it doesn't inherit JsonVariant directly so we can better control which
        /// constructors are allowed
        class Value
        {
        public:
            Value(std::nullptr_t = nullptr);
            Value(std::string_view s);
            Value(const std::string& s);
            Value(std::string&& s);
            Value(const char* s);
            Value(const bool b);
            Value(const Object& o);
            Value(Object&& o);
            Value(const Array& a);
            Value(Array&& a);
            Value(const std::initializer_list<Value>& init);
            Value(const NetworkType& o);

            // Add support for any std::vector<T>, std::deque<T>, std::list<T> etc... when T is compatible with Value
            template<
                template<typename, typename> class C,
                typename T,
                typename A = std::allocator<T>,
                std::enable_if_t<std::is_convertible_v<T, Value>, bool> = true
            >
            Value(const C<T, A>& c);

            // Add support for any std::array<T, N> when T is compatible with Value
            template<
                typename T,
                size_t N,
                std::enable_if_t<std::is_convertible_v<T, Value>, bool> = true
            >
            Value(const std::array<T, N>& v);

            // Add support for any std::map<std::string, T> when T is compatible with Value
            template<
                typename T,
                std::enable_if_t<std::is_convertible_v<T, Value>, bool> = true
            >
            Value(const std::map<std::string, T>& m);

            // Add support for all (unsigned) int/char/short
            template<
                typename T,
                std::enable_if_t<std::is_integral_v<T>&& std::is_unsigned_v<T>, bool> = true
            >
            Value(const T u);

            template<
                typename T,
                std::enable_if_t<(std::is_integral_v<T>&& std::is_signed_v<T>) || std::is_enum_v<T>, bool> = true
            >
            Value(const T i);

            template<
                typename T,
                std::enable_if_t<std::is_floating_point_v<T>, bool> = true
            >
            Value(const T f);

            template<
                typename T,
                std::enable_if_t<!std::is_same_v<T, std::monostate> && !std::is_same_v<T, Object> && !std::is_same_v<T, Array> && !std::is_same_v<T, std::string>, bool> = true
            >
            T get() const;

            template<typename T = double>
            T get_number() const;

            template<
                typename T,
                std::enable_if_t<std::is_same_v<T, Object> || std::is_same_v<T, Array> || std::is_same_v<T, std::string>, bool> = true
            >
            T& get();

            template<
                typename T,
                std::enable_if_t<std::is_same_v<T, Object> || std::is_same_v<T, Array> || std::is_same_v<T, std::string>, bool> = true
            >
            const T& get() const;

            Object& get_object();
            Array& get_array();
            std::string& get_string();

            const Object& get_object() const;
            const Array& get_array() const;
            const std::string& get_string() const;

            template<typename T>
            bool is() const;

            bool is_null() const;
            bool is_string() const;
            bool is_object() const;
            bool is_array() const;
            bool is_bool() const;
            bool is_integer() const;
            bool is_number() const;

            Value& operator[](const std::string& s);
            const Value& operator[](const std::string& s) const;

            Value& operator[](const size_t i);
            const Value& operator[](const size_t i) const;

            friend std::istream& operator>>(std::istream& is, Value& v);

            bool contains(const std::string& s) const;

            size_t size() const;
            void push_back(const Value& value);
            void push_back(Value&& value);

            /// @brief public dump interface
            /// @param indent number of char (space) for indentation. If -1, no new
            /// line will be added between values
            /// @param indent_char char used for indentation
            /// @return the string representation of this Value
            std::string Dump(const int indent = -1, const char indent_char = ' ') const;

        private:
            /// @brief private dump interface
            /// @param depth_level depth of this Value in the tree
            /// @param indent number of char (space) for indentation
            /// @param indent_char char used for indentation
            /// @return the string representation of this Value
            std::string Dump(const size_t depth_level, const int indent, const char indent_char) const;

            Internal::JsonVariant val;
        };

        /// @brief Real class declaration, just a derived class of std::vector<Value>
        class Array : public std::vector<Value>
        {
            using std::vector<Value>::vector;
        };

        /// @brief Real class declaration, just a derived class of std::map<std::string, Value>
        class Object : public std::map<std::string, Value>
        {
            using std::map<std::string, Value>::map;
        };

        /// @brief Parse a string_view from iter for at most length characters
        /// @param iter start character
        /// @param length available number of characters
        /// @param no_except if true, the function will return empty Value
        /// instead of throwing an exception in case of unvalid string
        /// @return The parsed Value, will throw a std::runtime_error if unvalid
        Value Parse(std::string_view::const_iterator iter, size_t length, bool no_except = false);

        /// @brief Parse a std::string
        /// @param s string to parse
        /// @param no_except if true, the function will return empty Value
        /// instead of throwing an exception in case of unvalid string
        /// @return The parsed Value, will throw a std::runtime_error if unvalid
        Value Parse(const std::string& s, bool no_except = false);



        // Templates implementations, they need to be below
        // Object and Array class so they are not incomplete
        // any more

        template<
            template<typename, typename> class C,
            typename T,
            typename A,
            std::enable_if_t<std::is_convertible_v<T, Value>, bool>
        >
        Value::Value(const C<T, A>& c) : val(Array())
        {
            for (const auto& i : c)
            {
                push_back(i);
            }
        }

        template<
            typename T,
            size_t N,
            std::enable_if_t<std::is_convertible_v<T, Value>, bool>
        >
        Value::Value(const std::array<T, N>& v) : val(Array())
        {
            for (const auto& i : v)
            {
                push_back(i);
            }
        }

        template<
            typename T,
            std::enable_if_t<std::is_convertible_v<T, Value>, bool>
        >
        Value::Value(const std::map<std::string, T>& m) : val(Object())
        {
            for (const auto& [k, v] : m)
            {
                operator[](k) = v;
            }
        }

        template<
            typename T,
            std::enable_if_t<std::is_integral_v<T>&& std::is_unsigned_v<T>, bool>
        >
        Value::Value(const T u) : val(static_cast<unsigned long long int>(u))
        {

        }

        template<
            typename T,
            std::enable_if_t<(std::is_integral_v<T>&& std::is_signed_v<T>) || std::is_enum_v<T>, bool>
        >
        Value::Value(const T i) : val(static_cast<long long int>(i))
        {

        }

        template<
            typename T,
            std::enable_if_t<std::is_floating_point_v<T>, bool>
        >
        Value::Value(const T f) : val(static_cast<double>(f))
        {

        }

        template<
            typename T,
            std::enable_if_t<!std::is_same_v<T, std::monostate> && !std::is_same_v<T, Object> && !std::is_same_v<T, Array> && !std::is_same_v<T, std::string>, bool>
        >
        T Value::get() const
        {
            if constexpr (std::is_same_v<T, bool>)
            {
                if (!std::holds_alternative<bool>(val))
                {
                    throw std::runtime_error("Trying to get the wrong type from Json::Value");
                }
                return std::get<bool>(val);
            }
            // Wrapper to be able to get char/short/int
            else if constexpr (std::is_integral_v<T>)
            {
                if (std::holds_alternative<long long int>(val))
                {
                    return static_cast<T>(std::get<long long int>(val));
                }
                else if (std::holds_alternative<unsigned long long int>(val))
                {
                    return static_cast<T>(std::get<unsigned long long int>(val));
                }
                else
                {
                    throw std::runtime_error("Trying to get an integral value from a Json::Value that is something else");
                }
            }
            // Wrapper to be able to get float/long double
            else if constexpr (std::is_floating_point_v<T>)
            {
                if (std::holds_alternative<double>(val))
                {
                    return static_cast<T>(std::get<double>(val));
                }
                else
                {
                    throw std::runtime_error("Trying to get a floating point value from a Json::Value that is something else");
                }
            }
            else
            {
                if (!std::holds_alternative<T>(val))
                {
                    throw std::runtime_error("Trying to get the wrong type from Json::Value");
                }
                return std::get<T>(val);
            }
        }

        template<typename T>
        T Value::get_number() const
        {
            if (std::holds_alternative<double>(val))
            {
                return static_cast<T>(std::get<double>(val));
            }
            else if (std::holds_alternative<long long int>(val))
            {
                return static_cast<T>(std::get<long long int>(val));
            }
            else if (std::holds_alternative<unsigned long long int>(val))
            {
                return static_cast<T>(std::get<unsigned long long int>(val));
            }
            else
            {
                throw std::runtime_error("Trying to get a number value from a Json::Value that is something else");
            }
        }

        template<
            typename T,
            std::enable_if_t<std::is_same_v<T, Object> || std::is_same_v<T, Array> || std::is_same_v<T, std::string>, bool>
        >
        T& Value::get()
        {
            // special case for object (removing the RecursiveWrapper)
            if constexpr (std::is_same_v<T, Object>)
            {
                if (!std::holds_alternative<ProtocolCraft::Internal::RecursiveWrapper<Object>>(val))
                {
                    throw std::runtime_error("Trying to get the wrong type from Json::Value");
                }
                return std::get<ProtocolCraft::Internal::RecursiveWrapper<Object>>(val).get();
            }
            // special case for array (removing the RecursiveWrapper)
            else if constexpr (std::is_same_v<T, Array>)
            {
                if (!std::holds_alternative<ProtocolCraft::Internal::RecursiveWrapper<Array>>(val))
                {
                    throw std::runtime_error("Trying to get the wrong type from Json::Value");
                }
                return std::get<ProtocolCraft::Internal::RecursiveWrapper<Array>>(val).get();
            }
            // all other cases (only std::string for now) should work with generic template
            else
            {
                if (!std::holds_alternative<T>(val))
                {
                    throw std::runtime_error("Trying to get the wrong type from Json::Value");
                }
                return std::get<T>(val);
            }
        }

        template<
            typename T,
            std::enable_if_t<std::is_same_v<T, Object> || std::is_same_v<T, Array> || std::is_same_v<T, std::string>, bool>
        >
        const T& Value::get() const
        {
            // special case for object (removing the RecursiveWrapper)
            if constexpr (std::is_same_v<T, Object>)
            {
                if (!std::holds_alternative<ProtocolCraft::Internal::RecursiveWrapper<Object>>(val))
                {
                    throw std::runtime_error("Trying to get the wrong type from Json::Value");
                }
                return std::get<ProtocolCraft::Internal::RecursiveWrapper<Object>>(val).get();
            }
            // special case for array (removing the RecursiveWrapper)
            else if constexpr (std::is_same_v<T, Array>)
            {
                if (!std::holds_alternative<ProtocolCraft::Internal::RecursiveWrapper<Array>>(val))
                {
                    throw std::runtime_error("Trying to get the wrong type from Json::Value");
                }
                return std::get<ProtocolCraft::Internal::RecursiveWrapper<Array>>(val).get();
            }
            // all other cases (only std::string for now) should work with generic template
            else
            {
                if (!std::holds_alternative<T>(val))
                {
                    throw std::runtime_error("Trying to get the wrong type from Json::Value");
                }
                return std::get<T>(val);
            }
        }

        template<typename T>
        bool Value::is() const
        {
            if constexpr (std::is_same_v<T, Object>)
            {
                return std::holds_alternative<ProtocolCraft::Internal::RecursiveWrapper<Object>>(val);
            }
            else if constexpr (std::is_same_v<T, Array>)
            {
                return std::holds_alternative<ProtocolCraft::Internal::RecursiveWrapper<Array>>(val);
            }
            else
            {
                return std::holds_alternative<T>(val);
            }
        }
    }
}
