#pragma once

#include <memory>
#include <string>

#include "botcraft/Network/BinaryReadWrite.hpp"

namespace Botcraft
{
    enum class TagType
    {
        End = 0,
        Byte,
        Short,
        Int,
        Long,
        Float,
        Double,
        ByteArray,
        String,
        List,
        Compound,
        IntArray,
        LongArray
    };

    class Tag
    {
    public:
        Tag();
        ~Tag();

        static std::shared_ptr<Tag> CreateTag(const TagType type);
        static const std::string TagTypeToString(const TagType type);

        virtual const TagType GetType() const = 0;
        virtual void Read(ReadIterator &iterator, size_t &length) = 0;
        virtual void Write(WriteContainer &container) const = 0;
        virtual const std::string Print(const std::string &prefix) const = 0;
    };
}