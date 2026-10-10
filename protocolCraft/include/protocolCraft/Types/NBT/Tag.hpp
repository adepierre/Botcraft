#pragma once

#include <variant>
#include <vector>
#include <string>
#include <utility>
#include <map>

#include "protocolCraft/Utilities/RecursiveWrapper.hpp"
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    namespace NBT
    {
        using TagEnd = std::monostate;
        using TagByte = char;
        using TagShort = short;
        using TagInt = int;
        using TagLong = long long int;
        using TagFloat = float;
        using TagDouble = double;
        using TagByteArray = std::vector<char>;
        using TagString = std::string;
        class TagList;
        class TagCompound;
        using TagIntArray = std::vector<int>;
        using TagLongArray = std::vector<long long int>;

        enum class TagType : char
        {
            TagEnd = 0,
            TagByte,
            TagShort,
            TagInt,
            TagLong,
            TagFloat,
            TagDouble,
            TagByteArray,
            TagString,
            TagList,
            TagCompound,
            TagIntArray,
            TagLongArray
        };

        namespace Internal
        {
            using TagVariant = std::variant<
                TagEnd,
                TagByte,
                TagShort,
                TagInt,
                TagLong,
                TagFloat,
                TagDouble,
                TagByteArray,
                TagString,
                ProtocolCraft::Internal::RecursiveWrapper<TagList>,
                ProtocolCraft::Internal::RecursiveWrapper<TagCompound>,
                TagIntArray,
                TagLongArray
            >;

            using TagListVariant = std::variant<
                std::vector<TagEnd>,
                std::vector<TagByte>,
                std::vector<TagShort>,
                std::vector<TagInt>,
                std::vector<TagLong>,
                std::vector<TagFloat>,
                std::vector<TagDouble>,
                std::vector<TagByteArray>,
                std::vector<TagString>,
                std::vector<TagList>,
                std::vector<TagCompound>,
                std::vector<TagIntArray>,
                std::vector<TagLongArray>
            >;
        }

        class Tag : public NetworkType
        {
        public:
            Tag() = default;

            template <typename T, std::enable_if_t<std::is_constructible_v<Internal::TagVariant, T&&>, bool> = true>
            Tag(T&& v) : val(std::forward<T>(v)) {}

            template<typename T>
            bool is() const;

            template<
                typename T,
                std::enable_if_t<std::is_convertible_v<std::vector<T>, Internal::TagListVariant>, bool> = true
            >
            bool is_list_of() const;

            template<typename T>
            const T& get() const;

            template<typename T>
            T& get();

            template<
                typename T,
                std::enable_if_t<std::is_convertible_v<std::vector<T>, Internal::TagListVariant>, bool> = true
            >
            const std::vector<T>& as_list_of() const;

            /// @brief Empty Tag becomes an empty TagList
            template<
                typename T,
                std::enable_if_t<std::is_convertible_v<std::vector<T>, Internal::TagListVariant>, bool> = true
            >
            std::vector<T>& as_list_of();

            const Tag& operator[](const std::string& s) const;
            Tag& operator[](const std::string& s);

            size_t size() const;
            bool contains(const std::string& s) const;

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
            virtual void WriteImpl(WriteContainer& container) const override;
            std::string ReadNamed(ReadIterator& iter, size_t& length);
            void WriteNamed(const std::string& tag_name, WriteContainer& container) const;
            virtual Json::Value SerializeImpl() const override;

        private:
            void ReadPayload(const TagType type, ReadIterator& iter, size_t& length);
            void WritePayload(WriteContainer& container) const;

            friend class TagCompound;

        private:
            Internal::TagVariant val;
        };


        class TagList : public NetworkType
        {
        public:
            TagList() = default;
            template<typename T, std::enable_if_t<std::is_convertible_v<std::vector<T>, Internal::TagListVariant>, bool> = true>
            TagList(std::vector<T> v) : vals(std::move(v)) {}

            size_t size() const;

            template<
                typename T,
                std::enable_if_t<std::is_convertible_v<std::vector<T>, Internal::TagListVariant>, bool> = true
            >
            bool is_of() const;

            template<
                typename T,
                std::enable_if_t<std::is_convertible_v<std::vector<T>, Internal::TagListVariant>, bool> = true
            >
            const std::vector<T>& as_list_of() const;

            template<
                typename T,
                std::enable_if_t<std::is_convertible_v<std::vector<T>, Internal::TagListVariant>, bool> = true
            >
            std::vector<T>& as_list_of();

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
            virtual void WriteImpl(WriteContainer& container) const override;
            virtual Json::Value SerializeImpl() const override;

        private:
            Internal::TagListVariant vals;
        };


        class TagCompound : public std::map<std::string, Tag>, public NetworkType
        {
            using std::map<std::string, Tag>::map;

        public:
            using std::map<std::string, Tag>::operator[];
            const Tag& operator[](const std::string& s) const;
            bool contains(const std::string& s) const;

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
            virtual void WriteImpl(WriteContainer& container) const override;
            virtual Json::Value SerializeImpl() const override;
        };




        template<typename T>
        bool Tag::is() const
        {
            if constexpr (std::is_same_v<T, TagList>)
            {
                return std::holds_alternative<ProtocolCraft::Internal::RecursiveWrapper<TagList>>(val);
            }
            else if constexpr (std::is_same_v<T, TagCompound>)
            {
                return std::holds_alternative<ProtocolCraft::Internal::RecursiveWrapper<TagCompound>>(val);
            }
            else
            {
                return std::holds_alternative<T>(val);
            }
        }

        template<
            typename T,
            std::enable_if_t<std::is_convertible_v<std::vector<T>, Internal::TagListVariant>, bool>
        >
        bool Tag::is_list_of() const
        {
            return is<TagList>() && get<TagList>().is_of<T>();
        }

        template<typename T>
        const T& Tag::get() const
        {
            if (!is<T>())
            {
                throw std::runtime_error("Trying to get the wrong type from NBT::Tag");
            }
            // special case for TagList and TagCompound (removing the RecursiveWrapper)
            if constexpr (std::is_same_v<T, TagList> || std::is_same_v<T, TagCompound>)
            {
                return std::get<ProtocolCraft::Internal::RecursiveWrapper<T>>(val).get();
            }
            else
            {
                return std::get<T>(val);
            }
        }

        template<typename T>
        T& Tag::get()
        {
            return const_cast<T&>(std::as_const(*this).get<T>());
        }

        template<
            typename T,
            std::enable_if_t<std::is_convertible_v<std::vector<T>, Internal::TagListVariant>, bool>
        >
        const std::vector<T>& Tag::as_list_of() const
        {
            if (!std::holds_alternative<ProtocolCraft::Internal::RecursiveWrapper<TagList>>(val))
            {
                throw std::runtime_error("Trying to get a list from another NBT::Tag type");
            }
            return get<TagList>().as_list_of<T>();
        }

        template<
            typename T,
            std::enable_if_t<std::is_convertible_v<std::vector<T>, Internal::TagListVariant>, bool>
        >
        std::vector<T>& Tag::as_list_of()
        {
            if (is<TagEnd>())
            {
                val = TagList();
            }
            return get<TagList>().as_list_of<T>();
        }



        template<
            typename T,
            std::enable_if_t<std::is_convertible_v<std::vector<T>, Internal::TagListVariant>, bool>
        >
        bool TagList::is_of() const
        {
            return std::holds_alternative<std::vector<T>>(vals);
        }

        template<
            typename T,
            std::enable_if_t<std::is_convertible_v<std::vector<T>, Internal::TagListVariant>, bool>
        >
        const std::vector<T>& TagList::as_list_of() const
        {
            if (!std::holds_alternative<std::vector<T>>(vals))
            {
                throw std::runtime_error("Trying to get the wrong type from NBT::TagList");
            }
            return std::get<std::vector<T>>(vals);
        }

        template<
            typename T,
            std::enable_if_t<std::is_convertible_v<std::vector<T>, Internal::TagListVariant>, bool>
        >
        std::vector<T>& TagList::as_list_of()
        {
            if (size() == 0)
            {
                vals = std::vector<T>();
            }
            return const_cast<std::vector<T>&>(std::as_const(*this).as_list_of<T>());
        }
    }
}
