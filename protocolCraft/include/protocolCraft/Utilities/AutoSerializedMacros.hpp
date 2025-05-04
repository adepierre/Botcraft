#pragma once

/// @brief Define a condition that can be used later inside an Internal::Conditioned type
#define DEFINE_CONDITION(Name, ...) private: bool Name() const { return __VA_ARGS__; } static_assert(true, "Forcing ;")

#ifdef PROTOCOLCRAFT_DETAILED_PARSING
#define _OFFSETS_DECLARATION(Name)                                      \
    using Name##_offset_type =                                          \
        Internal::OffsetType<typename Name##_type::storage_type>::type; \
    Name##_offset_type Name##_start{};                                  \
    Name##_offset_type Name##_end{}
#define _OFFSETS_FIELDS_DATA_DECLARATION(Name)                    \
    using field_offset_type = Name##_offset_type;                 \
    template <typename Parent> static constexpr field_offset_type \
        Parent::* field_start_offset_ptr = &Parent::Name##_start; \
    template <typename Parent> static constexpr field_offset_type \
        Parent::* field_end_offset_ptr = &Parent::Name##_end
#else
#define _OFFSETS_DECLARATION(Name)
#define _OFFSETS_FIELDS_DATA_DECLARATION(Name)
#endif

/// @brief Define a field that will be automatically integrated in Read/Write and Json serialization
/// We start by retrieving the SerializedType of the given type and create the actual class member.
/// Then we find the index of this field by counting how many FieldsData<size_t, T> template class
/// have already been defined. Last part defines a templated FieldsData struct with all the
/// name/type/member pointer info for this field.
/// For the name, we want to define it in PascalCase but we also need a camel_case litteral
/// version for json serialization, hence the constexpr string processing
/// For field_ptr we don't know the name of the current class so to avoid passing it to the macro
/// we use a template class instead. See GetField in DEFINE_UTILITIES for example of how to use it.
/// @param name field name
/// @param ... field type (passed as VA_ARGS because it can contain some ,) /!\ if Name == Type,
/// use the fully qualified type instead (like ProtocolCraft::Type instead of Type)
#define SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Name, ...)                        \
    private:                                                                     \
        using Name##_type = typename Internal::SerializedType<__VA_ARGS__>;      \
        Name##_type::storage_type Name{};                                        \
        _OFFSETS_DECLARATION(Name);                                              \
        template <size_t, typename> struct FieldsData;                           \
        static constexpr size_t Name##_index =                                   \
            Internal::field_index<0, struct FieldDummy##Name, FieldsData>;       \
        template <typename T>                                                    \
        struct FieldsData<Name##_index, T> {                                     \
            static constexpr std::array name_array =                             \
                Internal::ToSnakeCase<Internal::GetSnakeCaseSize(#Name)>(#Name); \
            static constexpr std::string_view field_name =                       \
                Internal::ToStringView<std::size(name_array)>(name_array);       \
            using field_type = __VA_ARGS__;                                      \
            using field_storage_type = Name##_type::storage_type;                \
            using field_serialization_type = Name##_type::serialization_type;    \
            template <typename Parent> static constexpr field_storage_type       \
                Parent::*field_ptr = &Parent::Name;                              \
            _OFFSETS_FIELDS_DATA_DECLARATION(Name);                              \
        };                                                                       \
        static_assert(true, "Forcing ;")


// Basically just a Get and a Set function, by value if it's a simple type, and by const ref if not
// We don't set an intermediate using with Name##_type::storage_type otherwise IDE autocomplete would
// display the name of the using instead of the real underlying type
#define GETTER(Name)                                                                                                         \
    public:                                                                                                                  \
        std::conditional_t<std::is_arithmetic_v<Name##_type::storage_type> || std::is_enum_v<Name##_type::storage_type>,     \
            Name##_type::storage_type, const Name##_type::storage_type&> Get##Name() const { return Name; }                  \
        static_assert(true, "Forcing ;")

#define SETTER(Name)                                                                                                         \
    public:                                                                                                                  \
        auto& Set##Name(                                                                                                     \
            std::conditional_t<std::is_arithmetic_v<Name##_type::storage_type> || std::is_enum_v<Name##_type::storage_type>, \
            Name##_type::storage_type, const Name##_type::storage_type&> Name##_) { Name = Name##_; return *this; }          \
        static_assert(true, "Forcing ;")

#define GETTER_SETTER(Name) GETTER(Name); SETTER(Name)

#define SERIALIZED_FIELD(Name, ...)                            \
    SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Name, __VA_ARGS__); \
    GETTER_SETTER(Name)

/// @brief Declare ReadImpl virtual function for auto serializable types
#define DECLARE_READ protected: virtual void ReadImpl(ReadIterator& iter, size_t& length) override
/// @brief Declare WriteImpl virtual function for auto serializable types
#define DECLARE_WRITE protected: virtual void WriteImpl(WriteContainer& container) const override
/// @brief Declare SerializeImpl virtual function for auto serializable types
#define DECLARE_SERIALIZE protected: virtual Json::Value SerializeImpl() const override


#ifdef PROTOCOLCRAFT_DETAILED_PARSING
#define _DEFINE_OFFSETS_UTILITIES                                                                                       \
    template <size_t i> auto& GetFieldStartOffset() {                                                                   \
        return this->*FieldsData<i, void>::template field_start_offset_ptr<std::remove_reference_t<decltype(*this)>>; } \
    template <size_t i> auto& GetFieldEndOffset() {                                                                     \
        return this->*FieldsData<i, void>::template field_end_offset_ptr<std::remove_reference_t<decltype(*this)>>; }   \
    template <size_t i> const auto& GetFieldStartOffset() const {                                                       \
        return this->*FieldsData<i, void>::template field_start_offset_ptr<std::remove_reference_t<decltype(*this)>>; } \
    template <size_t i> const auto& GetFieldEndOffset() const {                                                         \
        return this->*FieldsData<i, void>::template field_end_offset_ptr<std::remove_reference_t<decltype(*this)>>; }
#else
#define _DEFINE_OFFSETS_UTILITIES
#endif

/// @brief Define some constexpr utilities used to deal with the auto serializable fields
/// We use void as the unique identifier type template parameter for FieldsData as we are
/// sure it'll be different from what was used for the fields
#define DEFINE_UTILITIES                                                                                        \
    private:                                                                                                    \
        template <size_t, typename> struct FieldsData;                                                          \
        static constexpr size_t num_fields = Internal::field_index<0, void, FieldsData>;                        \
        template <size_t i> static constexpr std::string_view field_name = FieldsData<i, void>::field_name;     \
        template <size_t i> using field_type = typename FieldsData<i, void>::field_type;                        \
        template <size_t i> using field_storage_type = typename FieldsData<i, void>::field_storage_type;        \
        template <size_t i> using field_serialization_type =                                                    \
            typename FieldsData<i, void>::field_serialization_type;                                             \
        template <size_t i> auto& GetField() {                                                                  \
            return this->*FieldsData<i, void>::template field_ptr<std::remove_reference_t<decltype(*this)>>; }  \
        template <size_t i> const auto& GetField() const {                                                      \
             return this->*FieldsData<i, void>::template field_ptr<std::remove_reference_t<decltype(*this)>>; } \
        _DEFINE_OFFSETS_UTILITIES;                                                                              \
    static_assert(true, "Forcing ;")

/// @brief Define auto serializable utilities and declare ReadImpl, WriteImpl and SerializeImpl virtual functions
#define DECLARE_READ_WRITE_SERIALIZE DEFINE_UTILITIES; DECLARE_READ; DECLARE_WRITE; DECLARE_SERIALIZE

#ifdef PROTOCOLCRAFT_DETAILED_PARSING
#define _OFFSETS_POINTERS , &this->GetFieldStartOffset<i>(), &this->GetFieldEndOffset<i>()
#else
#define _OFFSETS_POINTERS
#endif
/// @brief Define ReadImpl virtual function that loops through all auto serializable fields
#define DEFINE_READ(ClassName)                                           \
    void ClassName::ReadImpl(ReadIterator& iter, size_t& length) {       \
        Internal::loop<num_fields>([&](auto i) {                         \
        try {                                                            \
            auto& field = this->GetField<i>();                           \
            if constexpr (Internal::IsCustomType<field_type<i>>) {       \
                field = field_type<i>::Read(                             \
                    this, iter, length _OFFSETS_POINTERS);               \
            }                                                            \
            else if constexpr (Internal::IsConditioned<field_type<i>>) { \
                if (field_type<i>::Evaluate(this)) {                     \
                    if constexpr (field_type<i>::stored_as_optional) {   \
                        field = ReadData<                                \
                            typename field_storage_type<i>::value_type,  \
                            field_serialization_type<i>>(                \
                                iter, length _OFFSETS_POINTERS);         \
                    }                                                    \
                    else {                                               \
                        field = ReadData<                                \
                            field_storage_type<i>,                       \
                            field_serialization_type<i>>(                \
                                iter, length _OFFSETS_POINTERS);         \
                    }                                                    \
                }                                                        \
                else if constexpr (field_type<i>::stored_as_optional) {  \
                    field = std::nullopt;                                \
                }                                                        \
            }                                                            \
            else {                                                       \
                field = ReadData<                                        \
                    field_storage_type<i>,                               \
                    field_serialization_type<i>>(                        \
                        iter, length _OFFSETS_POINTERS);                 \
            }                                                            \
        }                                                                \
        catch (const std::exception& ex) {                               \
            throw std::runtime_error(std::string("While reading ") +     \
                std::string(field_name<i>) + " (" + std::to_string(i) +  \
                "th field) in " + #ClassName + "\n" + ex.what());        \
        }                                                                \
        });                                                              \
    } static_assert(true, "Forcing ;")

/// @brief Define WriteImpl virtual function that loops through all auto serializable fields
#define DEFINE_WRITE(ClassName)                                                     \
    void ClassName::WriteImpl(WriteContainer& container) const {                    \
        Internal::loop<num_fields>([&](auto i) {                                    \
            const auto& field = this->GetField<i>();                                \
            if constexpr (Internal::IsCustomType<field_type<i>>) {                  \
                field_type<i>::Write(this, field, container);                       \
            }                                                                       \
            else if constexpr (Internal::IsConditioned<field_type<i>>) {            \
                if (field_type<i>::Evaluate(this)) {                                \
                    if constexpr (field_type<i>::stored_as_optional) {              \
                        WriteData<                                                  \
                            typename field_storage_type<i>::value_type,             \
                            field_serialization_type<i>>(field.value(), container); \
                    }                                                               \
                    else {                                                          \
                        WriteData<                                                  \
                            field_storage_type<i>,                                  \
                            field_serialization_type<i>>(field, container);         \
                    }                                                               \
                }                                                                   \
            }                                                                       \
            else {                                                                  \
                WriteData<                                                          \
                    field_storage_type<i>,                                          \
                    field_serialization_type<i>>(field, container);                 \
            }                                                                       \
        });                                                                         \
    } static_assert(true, "Forcing ;")

// Define SerializeImpl virtual function for auto serializable types
#define DEFINE_SERIALIZE(ClassName)                                        \
    Json::Value ClassName::SerializeImpl() const {                         \
        Json::Value output;                                                \
        Internal::loop<num_fields>([&](auto i) {                           \
            const auto& field = this->GetField<i>();                       \
            std::optional<Json::Value> serialized = std::nullopt;          \
            if constexpr (Internal::IsCustomType<field_type<i>>) {         \
                serialized = field_type<i>::Serialize(                     \
                    this, field _OFFSETS_POINTERS);                        \
            }                                                              \
            else if constexpr (Internal::IsConditioned<field_type<i>>) {   \
                if (field_type<i>::Evaluate(this)) {                       \
                        serialized = SerializeType<field_storage_type<i>>( \
                            field _OFFSETS_POINTERS);                      \
                }                                                          \
            }                                                              \
            else {                                                         \
                serialized = SerializeType<field_storage_type<i>>(         \
                    field _OFFSETS_POINTERS);                              \
            }                                                              \
            if (serialized.has_value()) {                                  \
                output[std::string(field_name<i>)] = serialized.value();   \
            }                                                              \
        });                                                                \
        return output;                                                     \
    } static_assert(true, "Forcing ;")

// Define a NetworkType with auto serializable fields
#define DEFINE_NETWORK_TYPE(ClassName) \
    DEFINE_READ(ClassName);            \
    DEFINE_WRITE(ClassName);           \
    DEFINE_SERIALIZE(ClassName)

// Define a Packet with auto serializable fields
#define DEFINE_PACKET_CLASS(ClassName)   \
    DEFINE_READ(ClassName);               \
    DEFINE_WRITE(ClassName);              \
    DEFINE_SERIALIZE(ClassName);          \
    template class BasePacket<ClassName>
