#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NBT/TagCompound.hpp"

namespace ProtocolCraft
{
    class NBT : public NetworkType
    {
    public:
        NBT();
        NBT(const NBT& nbt);
        ~NBT();

        const TagCompound& GetRoot() const;
        const std::shared_ptr<Tag> GetTag(const std::string &s) const;
        const bool HasData() const;

        // TODO: add methods to deal with files // compression?

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        virtual const picojson::value SerializeImpl() const override;


    private:
        TagCompound root_tag;
        std::string root_name;
        bool has_data;
    };
}