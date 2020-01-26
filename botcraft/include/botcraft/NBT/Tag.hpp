#pragma once

#include <memory>
#include <string>

#include "botcraft/Protocol/NetworkType.hpp"

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

    class Tag : public NetworkType
    {
    public:
        Tag();
        ~Tag();

        static std::shared_ptr<Tag> CreateTag(const TagType type);
        static const std::string TagTypeToString(const TagType type);

        virtual const TagType GetType() const = 0;
    };
}