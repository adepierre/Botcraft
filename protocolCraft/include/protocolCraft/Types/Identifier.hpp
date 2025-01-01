#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class Identifier : public NetworkType
    {
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(RawString, std::string);

        DECLARE_READ_WRITE_SERIALIZE;

    public:
        bool operator <(const Identifier& rhs) const
        {
            return GetName() < rhs.GetName() ||
                (GetName() == rhs.GetName() && GetNamespace() < rhs.GetNamespace());
        }

        std::string GetName() const
        {
            const size_t split = RawString.find(':');
            return split == std::string::npos ? RawString : RawString.substr(split + 1);
        }

        auto& SetName(const std::string& name)
        {
            const std::string namespace_ = GetNamespace();
            RawString = namespace_.empty() ? name : (namespace_ + ':' + name);
            return *this;
        }

        std::string GetNamespace() const
        {
            const size_t split = RawString.find(':');
            return split == std::string::npos ? "" : RawString.substr(0, split);
        }

        auto& SetNamespace(const std::string& namespace_)
        {
            const std::string name = GetName();
            RawString = namespace_.empty() ? name : (namespace_ + ':' + name);
            return *this;
        }

        std::string GetFull() const
        {
            if (GetNamespace().empty())
            {
                return "minecraft:" + GetName();
            }
            else
            {
                return RawString;
            }
        }

        auto& SetRawString(const std::string& raw)
        {
            RawString = raw;
            return *this;
        }
    };
} // ProtocolCraft
