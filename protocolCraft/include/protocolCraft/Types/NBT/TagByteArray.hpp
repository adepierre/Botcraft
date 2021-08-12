#pragma once

#include <memory>

#include "protocolCraft/Types/NBT/Tag.hpp"

namespace ProtocolCraft
{
    class TagByteArray : public Tag
    {
    public:
        TagByteArray();
        virtual ~TagByteArray();

        const std::vector<char>& GetValues() const;
        void SetValues(const std::vector<char> &v);

        virtual const TagType GetType() const override;

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        virtual const nlohmann::json SerializeImpl() const override;

    private:
        std::vector<char> values;
    };
}