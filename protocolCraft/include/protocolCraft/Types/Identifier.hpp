#pragma once

#include "protocolCraft/NetworkType.hpp"

#include <string>

namespace ProtocolCraft 
{
    class Identifier : public NetworkType
    {
    public:

        Identifier()
        {

        }

        virtual ~Identifier() override
        {

        }
        
        const bool operator <(const Identifier& rhs) const
        {
            return name < rhs.name ||
                (name == rhs.name && namespace_ < rhs.namespace_);
        }

        void SetNamespace(const std::string& namespace__)
        {
            namespace_ = namespace__;
        }

        void SetName(const std::string& name_)
        {
            name = name_;
        }


        const std::string& GetNamespace() const
        {
            return namespace_;
        }

        const std::string& GetName() const
        {
            return name;
        }

        std::string GetFull() const
        {
            if (namespace_.empty())
            {
                return "minecraft:" + name;
            }
            else
            {
                return namespace_ + ':' + name;
            }
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            const std::string str = ReadData<std::string>(iter, length);
            const size_t split = str.find(':');

            if (split == std::string::npos)
            {
                namespace_ = "";
                name = str;
            }
            else
            {
                namespace_ = str.substr(0, split);
                name = str.substr(split + 1);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            if (namespace_.empty())
            {
                WriteData<std::string>(name, container);
            }
            else
            {
                WriteData<std::string>(namespace_ + ':' + name, container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["namespace"] = namespace_;
            output["name"] = name;


            return output;
        }

    private:
        std::string namespace_;
        std::string name;
    };
} // ProtocolCraft
