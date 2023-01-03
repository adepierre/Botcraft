#include "protocolCraft/Types/NBT/TagList.hpp"

namespace ProtocolCraft
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
       tags_type = static_cast<TagType>(ReadData<char>(iterator, length));

       // Read list
       tags = ReadVector<std::shared_ptr<Tag>, int>(iterator, length,
           [this](ReadIterator& i, size_t& l)
           {
               std::shared_ptr<Tag> output = Tag::CreateTag(tags_type);
               output->Read(i, l);
               return output;
           }
       );
    }

    void TagList::WriteImpl(WriteContainer &container) const
    {
        // Write type
        WriteData<char>(static_cast<char>(tags_type), container);

        WriteVector<std::shared_ptr<Tag>, int>(tags, container,
            [](const std::shared_ptr<Tag>& t, WriteContainer& c)
            {
                t->Write(c);
            }
        );
    }

    const nlohmann::json TagList::SerializeImpl() const
    {
        nlohmann::json output;

        output["type"] = Tag::TagTypeToString(tags_type);
        output["content"] = nlohmann::json::array();

        for (const auto& t : tags)
        {
            output["content"].push_back(t->Serialize());
        }

        return output;
    }
}