#pragma once

#include <variant>
#include <vector>
#include <string>
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
            const std::string& GetName() const;

            template<typename T>
            bool is() const;

            template<
                typename T,
                std::enable_if_t<std::is_convertible_v<std::vector<T>, Internal::TagListVariant>, bool> = true
            >
            bool is_list_of() const;

            template<
                typename T,
                std::enable_if_t<
                std::is_same_v<T, TagByte> ||
                std::is_same_v<T, TagShort> ||
                std::is_same_v<T, TagInt> ||
                std::is_same_v<T, TagLong> ||
                std::is_same_v<T, TagFloat> ||
                std::is_same_v<T, TagDouble>, bool
                > = true
            >
            T get() const;

            template<
                typename T,
                std::enable_if_t<
                std::is_same_v<T, TagByteArray> ||
                std::is_same_v<T, TagString> ||
                std::is_same_v<T, TagList> ||
                std::is_same_v<T, TagCompound> ||
                std::is_same_v<T, TagIntArray> ||
                std::is_same_v<T, TagLongArray>, bool
                > = true
            >
            const T& get() const;

            template<
                typename T,
                std::enable_if_t<std::is_convertible_v<std::vector<T>, Internal::TagListVariant>, bool> = true
            >
            const std::vector<T>& as_list_of() const;

            const Tag& operator[](const std::string& s) const;

            size_t size() const;
            bool contains(const std::string& s) const;

        protected:
            virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
            virtual void WriteImpl(WriteContainer& container) const override;
            virtual Json::Value SerializeImpl() const override;

        private:
            Internal::TagVariant val;
            std::string name;
        };


        class TagList : public NetworkType
        {
        public:
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

        template<
            typename T,
            std::enable_if_t<
            std::is_same_v<T, TagByte> ||
            std::is_same_v<T, TagShort> ||
            std::is_same_v<T, TagInt> ||
            std::is_same_v<T, TagLong> ||
            std::is_same_v<T, TagFloat> ||
            std::is_same_v<T, TagDouble>, bool
            >
        >
        T Tag::get() const
        {
            if (!std::holds_alternative<T>(val))
            {
                throw std::runtime_error("Trying to get the wrong type from NBT::Tag");
            }
            return std::get<T>(val);
        }

        template<
            typename T,
            std::enable_if_t<
            std::is_same_v<T, TagByteArray> ||
            std::is_same_v<T, TagString> ||
            std::is_same_v<T, TagList> ||
            std::is_same_v<T, TagCompound> ||
            std::is_same_v<T, TagIntArray> ||
            std::is_same_v<T, TagLongArray>, bool
            >
        >
        const T& Tag::get() const
        {
            // special case for TagCompound (removing the RecursiveWrapper)
            if constexpr (std::is_same_v<T, TagCompound>)
            {
                if (!std::holds_alternative<ProtocolCraft::Internal::RecursiveWrapper<TagCompound>>(val))
                {
                    throw std::runtime_error("Trying to get the wrong type from NBT::Tag");
                }
                return std::get<ProtocolCraft::Internal::RecursiveWrapper<TagCompound>>(val).get();
            }
            // special case for TagList (removing the RecursiveWrapper)
            else if constexpr (std::is_same_v<T, TagList>)
            {
                if (!std::holds_alternative<ProtocolCraft::Internal::RecursiveWrapper<TagList>>(val))
                {
                    throw std::runtime_error("Trying to get the wrong type from NBT::Tag");
                }
                return std::get<ProtocolCraft::Internal::RecursiveWrapper<TagList>>(val).get();
            }
            // all other cases should work with generic template
            else
            {
                if (!std::holds_alternative<T>(val))
                {
                    throw std::runtime_error("Trying to get the wrong type from NBT::Tag");
                }
                return std::get<T>(val);
            }
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
    }
}
