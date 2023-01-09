#include "protocolCraft/Types/NBT/TagEnd.hpp"

namespace ProtocolCraft
{
    TagEnd::TagEnd()
    {

    }

    TagEnd::~TagEnd()
    {

    }

    TagType TagEnd::GetType() const
    {
        return TagType::End;
    }

    void TagEnd::ReadImpl(ReadIterator &iterator, size_t &length)
    {

    }

    void TagEnd::WriteImpl(WriteContainer &container) const
    {

    }

    const nlohmann::json TagEnd::SerializeImpl() const
    {
        return nlohmann::json();
    }
}