#pragma once

// Declare ReadImpl virtual function for auto serializable types
#define DECLARE_READ protected: virtual void ReadImpl(ReadIterator& iter, size_t& length) override
// Declare WriteImpl virtual function for auto serializable types
#define DECLARE_WRITE protected: virtual void WriteImpl(WriteContainer& container) const override
// Declare SerializeImpl virtual function for auto serializable types
#define DECLARE_SERIALIZE protected: virtual Json::Value SerializeImpl() const override

// Declare ReadImpl, WriteImpl and SerializeImpl virtual functions for auto serializable types
#define DECLARE_READ_WRITE_SERIALIZE DECLARE_READ; DECLARE_WRITE; DECLARE_SERIALIZE

// Define a condition to be used inside a Internal::Conditioned type
#define DECLARE_CONDITION(Name, ...) private: bool Name() const { return __VA_ARGS__; } static_assert(true, "Forcing ;")

// Create all types and static variables without any internal field
#define DECLARE_EMPTY                                                     \
    private:                                                              \
        using FieldsTuple = std::tuple<>;                                 \
        Internal::SerializedType<FieldsTuple>::storage_type fields;       \
        enum class FieldsEnum { None = -1, NUM_FIELDS };                  \
        static constexpr std::array<std::string_view, 0> json_names = {}; \
        DECLARE_READ_WRITE_SERIALIZE

#define _ARGS(...) __VA_ARGS__
#define _STR_ARGS(...) #__VA_ARGS__
// Creates a tuple with the given types, and names its elements with Names. Both sets should be comma separated values between ()
#define DECLARE_FIELDS(Types, Names)                                                                                       \
    private:                                                                                                               \
        enum class FieldsEnum { None = -1, _ARGS Names, NUM_FIELDS };                                                      \
        using FieldsTuple = std::tuple<_ARGS Types>;                                                                       \
        Internal::SerializedType<FieldsTuple>::storage_type fields;                                                        \
        static constexpr std::array names =                                                                                \
            Internal::SplitComma<static_cast<size_t>(FieldsEnum::NUM_FIELDS)>(_STR_ARGS Names);                            \
        static constexpr std::array json_names_length =                                                                    \
            Internal::GetSnakeCaseSize<static_cast<size_t>(FieldsEnum::NUM_FIELDS)>(names);                                \
        static constexpr std::tuple tuple_json_names =                                                                     \
            Internal::ArrayToSnakeCaseTuple<static_cast<size_t>(FieldsEnum::NUM_FIELDS), json_names_length>(names);        \
        static constexpr std::array json_names = Internal::TupleOfArraysToArrayOfStr(tuple_json_names);                    \
        static_assert(std::size(json_names) == std::tuple_size_v<FieldsTuple>, "Fields types and names count don't match")


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
        auto& Set##name(                                                                                                     \
            std::conditional_t<std::is_arithmetic_v<name##_type::storage_type> || std::is_enum_v<name##_type::storage_type>, \
            name##_type::storage_type, const name##_type::storage_type&> name)                                               \
            { std::get<static_cast<size_t>(FieldsEnum::name)>(fields) = name; return *this; }                                \
        static_assert(true, "Forcing ;")

#define GETTER(name)                                                                                                     \
    public:                                                                                                              \
        using name##_type =                                                                                              \
            typename Internal::SerializedType<std::tuple_element_t<static_cast<size_t>(FieldsEnum::name), FieldsTuple>>; \
        std::conditional_t<std::is_arithmetic_v<name##_type::storage_type> || std::is_enum_v<name##_type::storage_type>, \
            name##_type::storage_type, const name##_type::storage_type&> Get##name() const                               \
            { return std::get<static_cast<size_t>(FieldsEnum::name)>(fields); }                                          \
        static_assert(true, "Forcing ;")


// Define ReadImpl virtual function for auto serializable types
#define DEFINE_READ(ClassName)                                                                        \
    void ClassName::ReadImpl(ReadIterator& iter, size_t& length) {                                    \
        Internal::loop<std::tuple_size_v<FieldsTuple>>([&](auto i) {                                  \
            using TupleElement = std::tuple_element_t<i, FieldsTuple>;                                \
            using SerializedElement = Internal::SerializedType<TupleElement>;                         \
            if constexpr (Internal::IsConditioned<TupleElement>) {                                    \
                if (TupleElement::Evaluate(this)) {                                                   \
                    std::get<i>(fields) = ReadData<                                               \
                        typename Internal::SerializedType<typename TupleElement::type>::storage_type, \
                        typename SerializedElement::serialization_type>(iter, length);                \
                }                                                                                     \
                else if constexpr (TupleElement::stored_as_optional) {                                \
                    std::get<i>(fields) = std::nullopt;                                           \
                }                                                                                     \
            }                                                                                         \
            else {                                                                                    \
                std::get<i>(fields) = ReadData<                                                       \
                    typename SerializedElement::storage_type,                                         \
                    typename SerializedElement::serialization_type>(iter, length);                    \
            }                                                                                         \
        });                                                                                           \
    } static_assert(true, "Forcing ;")

// Define WriteImpl virtual function for auto serializable types
#define DEFINE_WRITE(ClassName)                                                                                      \
    void ClassName::WriteImpl(WriteContainer& container) const {                                                     \
        Internal::loop<std::tuple_size_v<FieldsTuple>>([&](auto i) {                                                 \
            using TupleElement = std::tuple_element_t<i, FieldsTuple>;                                               \
            using SerializedElement = Internal::SerializedType<TupleElement>;                                        \
            if constexpr (Internal::IsConditioned<TupleElement>) {                                                   \
                if (TupleElement::Evaluate(this)) {                                                                  \
                    if constexpr (TupleElement::stored_as_optional) {                                                \
                        WriteData<                                                                                   \
                            typename Internal::SerializedType<typename TupleElement::type>::storage_type,            \
                            typename SerializedElement::serialization_type>(std::get<i>(fields).value(), container); \
                    }                                                                                                \
                    else {                                                                                           \
                        WriteData<                                                                                   \
                            typename Internal::SerializedType<typename TupleElement::type>::storage_type,            \
                            typename SerializedElement::serialization_type>(std::get<i>(fields), container);         \
                    }                                                                                                \
                }                                                                                                    \
            }                                                                                                        \
            else {                                                                                                   \
                WriteData<                                                                                           \
                    typename SerializedElement::storage_type,                                                        \
                    typename SerializedElement::serialization_type>(std::get<i>(fields), container);                 \
            }                                                                                                        \
        });                                                                                                          \
    } static_assert(true, "Forcing ;")

// Define SerializeImpl virtual function for auto serializable types
#define DEFINE_SERIALIZE(ClassName)                                                                        \
    Json::Value ClassName::SerializeImpl() const {                                                         \
        Json::Value output;                                                                                \
        Internal::loop<std::tuple_size_v<FieldsTuple>>([&](auto i) {                                       \
            using TupleElement = std::tuple_element_t<i, FieldsTuple>;                                     \
            using SerializedElement = Internal::SerializedType<TupleElement>;                              \
            std::optional<Json::Value> serialized = std::nullopt;                                          \
            if constexpr (Internal::IsConditioned<TupleElement>) {                                         \
                if (TupleElement::Evaluate(this)) {                                                        \
                    if constexpr (TupleElement::stored_as_optional) {                                      \
                        serialized = SerializeType<typename Internal::SerializedType<                      \
                            typename TupleElement::type>::storage_type>(std::get<i>(fields).value());      \
                    }                                                                                      \
                    else {                                                                                 \
                        serialized = SerializeType<typename Internal::SerializedType<                      \
                            typename TupleElement::type>::storage_type>(std::get<i>(fields));              \
                    }                                                                                      \
                }                                                                                          \
            }                                                                                              \
            else {                                                                                         \
                serialized = SerializeType<typename SerializedElement::storage_type>(std::get<i>(fields)); \
            }                                                                                              \
            if (serialized.has_value()) {                                                                  \
                output[std::string(json_names[i])] = serialized.value();                                   \
            }                                                                                              \
        });                                                                                                \
        return output;                                                                                     \
    } static_assert(true, "Forcing ;")

// Define a NetworkType with auto serializable fields
#define DEFINE_NETWORK_TYPE(ClassName) \
    DEFINE_READ(ClassName);            \
    DEFINE_WRITE(ClassName);           \
    DEFINE_SERIALIZE(ClassName)

// Define a Message with auto serializable fields
#define DEFINE_MESSAGE_CLASS(ClassName)   \
    DEFINE_READ(ClassName);               \
    DEFINE_WRITE(ClassName);              \
    DEFINE_SERIALIZE(ClassName);          \
    template class BaseMessage<ClassName>

// Define a Message with auto serializable fields, but custom ReadImpl/WriteImpl
#define DEFINE_SERIALIZED_MESSAGE_CLASS(ClassName) \
    DEFINE_SERIALIZE(ClassName);                   \
    template class BaseMessage<ClassName>

#define DEFINE_CUSTOM_SERIALIZED_MESSAGE_CLASS(ClassName) \
    DEFINE_READ(ClassName);                               \
    DEFINE_WRITE(ClassName);                              \
    template class BaseMessage<ClassName>

// Define a Message with auto serializable fields, but custom Impl methods
#define DEFINE_IMPLEMENTED_MESSAGE_CLASS(ClassName) template class BaseMessage<ClassName>
