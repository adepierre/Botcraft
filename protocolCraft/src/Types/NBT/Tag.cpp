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
        switch (type)
        {
        case TagType::End:
            return std::make_shared<TagEnd>();
        case TagType::Byte:
            return std::make_shared<TagByte>();
        case TagType::Short:
            return std::make_shared<TagShort>();
        case TagType::Int:
            return std::make_shared<TagInt>();
        case TagType::Long:
            return std::make_shared<TagLong>();
        case TagType::Float:
            return std::make_shared<TagFloat>();
        case TagType::Double:
            return std::make_shared<TagDouble>();
        case TagType::ByteArray:
            return std::make_shared<TagByteArray>();
        case TagType::String:
            return std::make_shared<TagString>();
        case TagType::List:
            return std::make_shared<TagList>();
        case TagType::Compound:
            return std::make_shared<TagCompound>();
        case TagType::IntArray:
            return std::make_shared<TagIntArray>();
        case TagType::LongArray:
            return std::make_shared<TagLongArray>();
        default:
            return nullptr;
        }
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