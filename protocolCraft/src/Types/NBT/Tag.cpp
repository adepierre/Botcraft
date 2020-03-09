#include "protocolCraft/Types/NBT/Tag.hpp"

#include "protocolCraft/Types/NBT/TagEnd.hpp"
#include "protocolCraft/Types/NBT/TagByte.hpp"
#include "protocolCraft/Types/NBT/TagShort.hpp"
#include "protocolCraft/Types/NBT/TagInt.hpp"
#include "protocolCraft/Types/NBT/TagLong.hpp"
#include "protocolCraft/Types/NBT/TagFloat.hpp"
#include "protocolCraft/Types/NBT/TagDouble.hpp"
#include "protocolCraft/Types/NBT/TagByteArray.hpp"
#include "protocolCraft/Types/NBT/TagString.hpp"
#include "protocolCraft/Types/NBT/TagList.hpp"
#include "protocolCraft/Types/NBT/TagCompound.hpp"
#include "protocolCraft/Types/NBT/TagIntArray.hpp"
#include "protocolCraft/Types/NBT/TagLongArray.hpp"

namespace ProtocolCraft
{
    Tag::Tag()
    {

    }

    Tag::~Tag()
    {

    }

    std::shared_ptr<Tag> Tag::CreateTag(const TagType type)
    {
        std::shared_ptr<Tag> output;

        switch (type)
        {
        case TagType::End:
            output = std::shared_ptr<TagEnd>(new TagEnd);
            break;
        case TagType::Byte:
            output = std::shared_ptr<TagByte>(new TagByte);
            break;
        case TagType::Short:
            output = std::shared_ptr<TagShort>(new TagShort);
            break;
        case TagType::Int:
            output = std::shared_ptr<TagInt>(new TagInt);
            break;
        case TagType::Long:
            output = std::shared_ptr<TagLong>(new TagLong);
            break;
        case TagType::Float:
            output = std::shared_ptr<TagFloat>(new TagFloat);
            break;
        case TagType::Double:
            output = std::shared_ptr<TagDouble>(new TagDouble);
            break;
        case TagType::ByteArray:
            output = std::shared_ptr<TagByteArray>(new TagByteArray);
            break;
        case TagType::String:
            output = std::shared_ptr<TagString>(new TagString);
            break;
        case TagType::List:
            output = std::shared_ptr<TagList>(new TagList);
            break;
        case TagType::Compound:
            output = std::shared_ptr<TagCompound>(new TagCompound);
            break;
        case TagType::IntArray:
            output = std::shared_ptr<TagIntArray>(new TagIntArray);
            break;
        case TagType::LongArray:
            output = std::shared_ptr<TagLongArray>(new TagLongArray);
            break;
        default:
            break;
        }

        return output;
    }

    const std::string Tag::TagTypeToString(const TagType type)
    {
        switch (type)
        {
        case TagType::End:
            return "";
        case TagType::Byte:
            return "TAG_Byte";
        case TagType::Short:
            return "TAG_Short";
        case TagType::Int:
            return "TAG_Int";
        case TagType::Long:
            return "TAG_Long";
        case TagType::Float:
            return "TAG_Float";
        case TagType::Double:
            return "TAG_Double";
        case TagType::ByteArray:
            return "TAG_Byte_Array";
        case TagType::String:
            return "TAG_String";
        case TagType::List:
            return "TAG_List";
        case TagType::Compound:
            return "TAG_Compound";
        case TagType::IntArray:
            return "TAG_Int_Array";
        case TagType::LongArray:
            return "TAG_Long_Array";
        default:
            return "";
        }
    }
}