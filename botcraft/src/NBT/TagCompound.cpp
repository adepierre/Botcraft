#include "botcraft/NBT/TagCompound.hpp"

namespace Botcraft
{
    TagCompound::TagCompound()
    {

    }

    TagCompound::~TagCompound()
    {

    }
    
    const std::map<std::string, std::shared_ptr<Tag> >& TagCompound::GetValues() const
    {
        return tags;
    }

    void TagCompound::SetValues(const std::map<std::string, std::shared_ptr<Tag> > &v)
    {
        tags = v;
    }

    const TagType TagCompound::GetType() const
    {
        return TagType::Compound;
    }

    void TagCompound::Read(ReadIterator &iterator, size_t &length)
    {
        while (true)
        {
            // Read type
            const TagType type = (TagType)ReadData<char>(iterator, length);

            std::shared_ptr<Tag> tag = Tag::CreateTag(type);

            // If it's an End tag, do not read the name
            if (type == TagType::End)
            {
                break;
            }

            // Read name size
            const unsigned short name_size = ReadData<unsigned short>(iterator, length);

            // Read name
            const std::string read_name = ReadRawString(iterator, length, name_size);

            // Read payload
            tag->Read(iterator, length);

            tags[read_name] = tag;
        }
    }

    void TagCompound::Write(WriteContainer &container) const
    {
        for (auto it = tags.begin(); it != tags.end(); ++it)
        {
            // Write type
            WriteData<char>((char)it->second->GetType(), container);
            
            // Write name size
            WriteData<unsigned short>(it->first.size(), container);
            
            // Write name
            WriteRawString(it->first, container);
            
            // Write payload
            it->second->Write(container);
        }

        // Add TAG_End
        WriteData<char>((char)TagType::End, container);
    }
    
    const std::string TagCompound::Print(const std::string &prefix) const
    {
        std::string output = std::to_string(tags.size()) + " entr" + (tags.size() > 1 ? "ies" : "y") + "\n"
            + prefix + "{\n";

        for (auto it = tags.begin(); it != tags.end(); ++it)
        {
            if (it->second->GetType() != TagType::End)
            {
                output += prefix + "    " + Tag::TagTypeToString(it->second->GetType()) + "('" + it->first + "'): " + it->second->Print(prefix + "    ") + "\n";
            }
        }
        output += prefix + "}";

        return  output;
    }
}