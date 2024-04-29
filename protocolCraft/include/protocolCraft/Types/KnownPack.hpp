#pragma once

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include <string>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class KnownPack : public NetworkType
    {
    public:
        virtual ~KnownPack() override
        {

        }


        void SetNamespace(const std::string& namespace__)
        {
            namespace_ = namespace__;
        }

        void SetId(const std::string& id__)
        {
            id_ = id__;
        }
        
        void SetVersion(const std::string& version_)
        {
            version = version_;
        }
    


        const std::string& GetNamespace() const
        {
            return namespace_;
        }

        const std::string& GetId_() const
        {
            return id_;
        }
        
        const std::string& GetVersion() const
        {
            return version;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            namespace_ = ReadData<std::string>(iter, length);
            id_ = ReadData<std::string>(iter, length);
            version = ReadData<std::string>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(namespace_, container);
            WriteData<std::string>(id_, container);
            WriteData<std::string>(version, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["namespace"] = namespace_;
            output["id"] = id_;
            output["version"] = version;

            return output;
        }

    private:
        std::string namespace_;
        std::string id_;
        std::string version;
    };
}
#endif
