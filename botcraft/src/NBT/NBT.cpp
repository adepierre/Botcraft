#include "botcraft/NBT/NBT.hpp"

namespace Botcraft
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
            root_tag.Write(container);
        }
        else
        {
            WriteData<char>((char)TagType::End, container);
        }
    }

    const picojson::value NBT::SerializeImpl() const
    {
        picojson::value value(picojson::object_type, false);
        picojson::object& object = value.get<picojson::object>();

        object["type"] = picojson::value("NBT");
        object["name"] = picojson::value(root_name);
        object["content"] = root_tag.Serialize();

        return value;
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