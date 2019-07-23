#include "botcraft/NBT/NBT.hpp"

namespace Botcraft
{
    NBT::NBT()
    {
        has_data = false;
    }

    NBT::~NBT()
    {

    }

    const TagCompound& NBT::GetRoot() const
    {
        return root_tag;
    }

    void NBT::Read(ReadIterator &iterator, size_t &length)
    {
        // Read type
        const TagType type = (TagType)ReadData<char>(iterator, length);

        // No data to read
        if (type == TagType::End)
        {
            has_data = false;
            return;
        }

        if (type != TagType::Compound)
        {
            throw(std::runtime_error("Error reading NBT, not starting with compound"));
        }

        // Read name size
        const unsigned short name_size = ReadData<unsigned short>(iterator, length);

        // Read name
        root_name = ReadRawString(iterator, length, name_size);

        root_tag.Read(iterator, length);
        has_data = true;
    }

    void NBT::Write(WriteContainer &container) const
    {
        root_tag.Write(container);
    }

    const std::string NBT::Print() const
    {
        return Tag::TagTypeToString(TagType::Compound) + "(): " + root_tag.Print("");
    }

    const std::shared_ptr<Tag> NBT::GetTag(const std::string &s) const
    {
        const std::map<std::string, std::shared_ptr<Tag> > &tags = root_tag.GetValues();

        auto it = tags.find(s);

        if (it == tags.end())
        {
            return nullptr;
        }

        return it->second;
    }
        
    const bool NBT::HasData() const
    {
        return has_data;
    }
}