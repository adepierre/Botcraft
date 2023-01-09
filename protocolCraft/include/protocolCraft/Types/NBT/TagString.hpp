#pragma once

#include <memory>

#include "protocolCraft/Types/NBT/Tag.hpp"

namespace ProtocolCraft
{
    class TagString : public Tag
    {
    public:
        TagString();
        virtual ~TagString();

        const std::string& GetValue() const;
        void SetValue(const std::string &v);

        virtual TagType GetType() const override;

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        virtual const nlohmann::json SerializeImpl() const override;

    private:
        std::string value;
    };
}
