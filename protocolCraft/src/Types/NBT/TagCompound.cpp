#include "protocolCraft/Types/NBT/TagCompound.hpp"

namespace ProtocolCraft
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

    const std::shared_ptr<Tag> TagCompound::GetValue(const std::string& name) const
    {
        auto it = tags.find(name);

        if (it == tags.end())
        {
            return nullptr;
        }

        return it->second;
    }

    void TagCompound::SetValues(const std::map<std::string, std::shared_ptr<Tag> > &v)
    {
        tags = v;
    }

    TagType TagCompound::GetType() const
    {
        return TagType::Compound;
    }

    void TagCompound::ReadImpl(ReadIterator &iterator, size_t &length)
    {
        while (true)
        {
            // Read type
            const TagType type = (TagType)ReadData<char>(iterator, length);

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
            std::shared_ptr<Tag> tag = Tag::CreateTag(type);
            tag->Read(iterator, length);

            tags[read_name] = tag;
        }
    }

    void TagCompound::WriteImpl(WriteContainer &container) const
    {
        for (auto it = tags.begin(); it != tags.end(); ++it)
        {
            // Write type
            WriteData<char>(static_cast<char>(it->second->GetType()), container);
            
            // Write name size
            WriteData<unsigned short>(static_cast<unsigned short>(it->first.size()), container);
            
            // Write name
            WriteRawString(it->first, container);
            
            // Write payload
            it->second->Write(container);
        }

        // Add TAG_End
        WriteData<char>(static_cast<char>(TagType::End), container);
    }
    
    const nlohmann::json TagCompound::SerializeImpl() const
    {
        nlohmann::json output = nlohmann::json::array();

        for (const auto& p : tags)
        {
            if (p.second->GetType() != TagType::End)
            {
                nlohmann::json current_item;

                current_item["type"] = Tag::TagTypeToString(p.second->GetType());
                current_item["name"] = p.first;
                current_item["content"] = p.second->Serialize();
                
                output.push_back(current_item);
            }
        }

        return output;
    }
}