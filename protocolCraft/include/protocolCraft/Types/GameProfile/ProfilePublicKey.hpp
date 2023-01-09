#if PROTOCOL_VERSION > 758
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include <string>
#include <map>

namespace ProtocolCraft 
{
    class ProfilePublicKey : public NetworkType
    {
    public:

        ProfilePublicKey()
        {

        }

        virtual ~ProfilePublicKey() override
        {

        }


        void SetTimestamp(const long long int timestamp_)
        {
            timestamp = timestamp_;
        }

        void SetKey(const std::vector<unsigned char>& key_)
        {
            key = key_;
        }

        void SetSignature(const std::vector<unsigned char>& signature_)
        {
            signature = signature_;
        }


        long long int GetTimestamp() const
        {
            return timestamp;
        }

        const std::vector<unsigned char>& GetKey() const
        {
            return key;
        }

        const std::vector<unsigned char>& GetSignature() const
        {
            return signature;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            timestamp = ReadData<long long int>(iter, length);
            key = ReadVector<unsigned char>(iter, length);
            signature = ReadVector<unsigned char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<long long int>(timestamp, container);
            WriteVector<unsigned char>(key, container);
            WriteVector<unsigned char>(signature, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["timestamp"] = timestamp;
            output["key"] = "Vector of " + std::to_string(key.size()) + " unsigned char";
            output["signature"] = "Vector of " + std::to_string(signature.size()) + " unsigned char";


            return output;
        }

    private:
        long long int timestamp;
        std::vector<unsigned char> key;
        std::vector<unsigned char> signature;
    };
} // ProtocolCraft
#endif
