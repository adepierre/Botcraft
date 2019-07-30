#include "botcraft/NBT/TagList.hpp"

namespace Botcraft
{
    TagList::TagList()
    {

    }

    TagList::~TagList()
    {

    }

    const std::vector<std::shared_ptr<Tag> >& TagList::GetValues() const
    {
        return tags;
    }

    void TagList::SetValues(const std::vector<std::shared_ptr<Tag> > &v)
    {
        tags = v;
    }

    const TagType TagList::GetTagsType() const
    {
        return tags_type;
    }

    void TagList::SetTagsType(const TagType tags_type_)
    {
        tags_type = tags_type_;
    }

    const TagType TagList::GetType() const
    {
        return TagType::List;
    }

    void TagList::ReadImpl(ReadIterator &iterator, size_t &length)
    {
        // Read type
       tags_type = (TagType)ReadData<char>(iterator, length);

       // Read list size
       const int list_size = ReadData<int>(iterator, length);

       tags = std::vector<std::shared_ptr<Tag> >(list_size);

       for (int i = 0; i < list_size; ++i)
       {
           tags[i] = Tag::CreateTag(tags_type);
           tags[i]->Read(iterator, length);
       }
    }

    void TagList::WriteImpl(WriteContainer &container) const
    {
        // Write type
        WriteData<char>((char)tags_type, container);

        // Write size
        WriteData<int>((int)tags.size(), container);

        for (int i = 0; i < tags.size(); ++i)
        {
            // Write payload
            tags[i]->Write(container);
        }
    }

    const std::string TagList::Print(const std::string &prefix) const
    {
        std::string output = std::to_string(tags.size()) + " entr" + (tags.size() > 1 ? "ies" : "y") + "\n"
            + prefix + "{\n";

        for (int i = 0; i < tags.size(); ++i)
        {
            output += prefix + "    " + Tag::TagTypeToString(tags_type) + "(None): " + tags[i]->Print(prefix + "    ") + "\n";
        }
        output += prefix + "}";

        return  output;
    }
}