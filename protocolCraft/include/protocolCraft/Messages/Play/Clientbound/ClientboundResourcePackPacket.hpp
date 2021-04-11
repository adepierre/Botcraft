#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundResourcePackPacket : public BaseMessage<ClientboundResourcePackPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x34;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x37;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x39;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x3A;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x39;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x38;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Ressource Pack";
        }

        void SetUrl(const std::string& url_)
        {
            url = url_;
        }

        void SetHash(const std::string& hash_)
        {
            hash = hash_;
        }


        const std::string& GetUrl() const
        {
            return url;
        }

        const std::string& GetHash() const
        {
            return hash;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            url = ReadString(iter, length);
            hash = ReadString(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteString(url, container);
            WriteString(hash, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["url"] = picojson::value(url);
            object["hash"] = picojson::value(hash);

            return value;
        }

    private:
        std::string url;
        std::string hash;

    };
} //ProtocolCraft