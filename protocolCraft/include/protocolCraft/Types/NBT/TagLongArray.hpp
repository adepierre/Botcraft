#pragma once

#include <memory>

#include "protocolCraft/Types/NBT/Tag.hpp"

namespace ProtocolCraft
{
    class TagLongArray : public Tag
    {
    public:
        TagLongArray();
        virtual ~TagLongArray();

        const std::vector<long long int>& GetValues() const;
        void SetValues(const std::vector<long long int> &v);

        virtual const TagType GetType() const override;

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        virtual const picojson::value SerializeImpl() const override;

    private:
        std::vector<long long int> values;
    };
}