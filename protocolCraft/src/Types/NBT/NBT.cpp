#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{
    NBT::NBT()
    {
        has_data = false;
    }

    NBT::NBT(const NBT& nbt)
    {
        root_tag = nbt.root_tag;
        root_name = nbt.root_name;
        has_data = nbt.has_data;
    }

    NBT::~NBT()
    {

    }

    const TagCompound& NBT::GetRoot() const
    {
        return root_tag;
    }

    void NBT::ReadImpl(ReadIterator &iterator, size_t &length)
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

    void NBT::WriteImpl(WriteContainer &container) const
    {
        if (has_data)
        {
            WriteData<char>((char)TagType::Compound, container);
            WriteData<unsigned short>(root_name.size(), container);
            WriteRawString(root_name, container);
            root_tag.Write(container);
        }
        else
        {
            WriteData<char>((char)TagType::End, container);
        }
    }

    const nlohmann::json NBT::SerializeImpl() const
    {
        nlohmann::json output;

        output["type"] = "NBT";
        output["name"] = root_name;
        output["content"] = root_tag.Serialize();

        return output;
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