#pragma once

#include "protocolCraft/Utilities/ConstexprStrProcessing.hpp"

// Create all types and static variables without any internal field
#define DECLARE_EMPTY                                               \
    private:                                                        \
        using FieldsTuple = std::tuple<>;                           \
        Internal::SerializedType<FieldsTuple>::storage_type fields; \
        friend struct PrivateFieldsAccessor;                        \
        enum class FieldsEnum { None = -1, NUM_FIELDS };            \
        static constexpr std::string_view raw_names = "";           \
        static const std::array<std::string_view, 0> json_names;

// Creates a tuple with the given types, adds FieldsTupleAccessor as friend
#define DECLARE_FIELDS_TYPES(...)                                  \
    private:                                                       \
        using FieldsTuple = std::tuple<__VA_ARGS__>;               \
        Internal::SerializedType<FieldsTuple>::storage_type fields

// Initialize fields names, must have the same number of elements than FieldsTuple
// json_names is only static const and not constexpr so all the constexpr stuff
// to get them from raw_names are done only once in a cpp file instead of
// once per TU including the class .hpp file
#define DECLARE_FIELDS_NAMES(...)                                     \
    private:                                                          \
        friend struct PrivateFieldsAccessor;                          \
        enum class FieldsEnum { None = -1, __VA_ARGS__, NUM_FIELDS }; \
        static constexpr std::string_view raw_names = #__VA_ARGS__;   \
        static const std::array<                                      \
            std::string_view,                                         \
            static_cast<int>(FieldsEnum::NUM_FIELDS)> json_names;     \
        static_assert(                                                \
            std::size(json_names) == std::tuple_size_v<FieldsTuple>,  \
            "Fields types and names count don't match"                \
        )

// Declare ReadImpl virtual function for auto serializable types
#define DECLARE_READ protected: virtual void ReadImpl(ReadIterator& iter, size_t& length) override
// Declare WriteImpl virtual function for auto serializable types
#define DECLARE_WRITE protected: virtual void WriteImpl(WriteContainer& container) const override
// Declare SerializeImpl virtual function for auto serializable types
#define DECLARE_SERIALIZE protected: virtual Json::Value SerializeImpl() const override

// Declare ReadImpl, WriteImpl and SerializeImpl virtual functions for auto serializable types
#define DECLARE_READ_WRITE_SERIALIZE DECLARE_READ; DECLARE_WRITE; DECLARE_SERIALIZE

// Basically just a Get and a Set function, by value if it's a simple type, and by const ref if not
// We don't use ::type in using name##_type so IDE autocomplete can still return the proper type
// otherwise they'd just return name##_type which is not as helpful
#define GETTER_SETTER(name)                                                                                                  \
    public:                                                                                                                  \
        using name##_type =                                                                                                  \
            typename Internal::SerializedType<std::tuple_element_t<static_cast<size_t>(FieldsEnum::name), FieldsTuple>>;     \
        std::conditional_t<std::is_arithmetic_v<name##_type::storage_type> || std::is_enum_v<name##_type::storage_type>,     \
            name##_type::storage_type, const name##_type::storage_type&> Get##name() const                                   \
            { return std::get<static_cast<size_t>(FieldsEnum::name)>(fields); }                                              \
        void Set##name(                                                                                                      \
            std::conditional_t<std::is_arithmetic_v<name##_type::storage_type> || std::is_enum_v<name##_type::storage_type>, \
            name##_type::storage_type, const name##_type::storage_type&> name)                                               \
            { std::get<static_cast<size_t>(FieldsEnum::name)>(fields) = name; }                                              \
        static_assert(true, "Forcing ;")

// Define ReadImpl virtual function for auto serializable types
#define DEFINE_READ(ClassName)                                     \
    void ClassName::ReadImpl(ReadIterator& iter, size_t& length) { \
        ReadTuple<FieldsTuple>(fields, iter, length);              \
    } static_assert(true, "Forcing ;")

// Define WriteImpl virtual function for auto serializable types
#define DEFINE_WRITE(ClassName)                                  \
    void ClassName::WriteImpl(WriteContainer& container) const { \
        WriteTuple<FieldsTuple>(fields, container);              \
    } static_assert(true, "Forcing ;")

// Define SerializeImpl virtual function for auto serializable types
#define DEFINE_SERIALIZE(ClassName)                             \
    Json::Value ClassName::SerializeImpl() const {              \
        return SerializeTuple<FieldsTuple>(fields, json_names); \
    } static_assert(true, "Forcing ;")

#define DEFINE_JSON_NAMES(ClassName)                                                      \
    namespace {                                                                           \
        static constexpr int ClassName##_num_fields =                                     \
            PrivateFieldsAccessor::num_fields<ClassName>;                                 \
        static constexpr std::array ClassName##_names =                                   \
            Internal::SplitComma<ClassName##_num_fields>(                                 \
                PrivateFieldsAccessor::raw_names<ClassName>);                             \
        static constexpr std::array ClassName##_json_names_length =                       \
                Internal::GetSnakeCaseSize<ClassName##_num_fields>(ClassName##_names);    \
        static constexpr std::tuple ClassName##_json_names =                              \
                Internal::ArrayToSnakeCaseTuple<                                          \
                    ClassName##_num_fields,                                               \
                    ClassName##_json_names_length>(ClassName##_names);                    \
    }                                                                                     \
    const std::array<                                                                     \
        std::string_view,                                                                 \
        ClassName##_num_fields                                                            \
    > ClassName::json_names = Internal::TupleOfArraysToArrayOfStr(ClassName##_json_names)

// Define a NetworkType with auto serializable fields
#define DEFINE_NETWORK_TYPE(ClassName) \
    DEFINE_JSON_NAMES(ClassName);      \
    DEFINE_READ(ClassName);            \
    DEFINE_WRITE(ClassName);           \
    DEFINE_SERIALIZE(ClassName)

// Define a NetworkType with auto serializable fields, but custom ReadImpl/WriteImpl
#define DEFINE_SERIALIZED_NETWORK_TYPE(ClassName) \
    DEFINE_JSON_NAMES(ClassName);                 \
    DEFINE_SERIALIZE(ClassName)

// Define a Message with auto serializable fields
#define DEFINE_MESSAGE_CLASS(ClassName)   \
    DEFINE_JSON_NAMES(ClassName);         \
    DEFINE_READ(ClassName);               \
    DEFINE_WRITE(ClassName);              \
    DEFINE_SERIALIZE(ClassName);          \
    template class BaseMessage<ClassName>

// Define a Message with auto serializable fields, but custom ReadImpl/WriteImpl
#define DEFINE_SERIALIZED_MESSAGE_CLASS(ClassName)   \
    DEFINE_JSON_NAMES(ClassName);                    \
    DEFINE_SERIALIZE(ClassName);                     \
    template class BaseMessage<ClassName>
