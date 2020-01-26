#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"

namespace Botcraft
{
    class EncryptionResponse : public BaseMessage<EncryptionResponse>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x01;
        }

        virtual const std::string GetName() const override
        {
            return "Encryption Response";
        }

        void SetSharedSecret(const std::vector<unsigned char> &shared_secret_)
        {
            shared_secret = shared_secret_;
            shared_secret_length = shared_secret_.size();
        }

        void SetVerifyToken(const std::vector<unsigned char>& verify_token_)
        {
            verify_token = verify_token_;
            verify_token_length = verify_token_.size();
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            std::cerr << "Severbound message" << std::endl;
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVarInt(shared_secret_length, container);
            WriteByteArray(shared_secret, container);
            WriteVarInt(verify_token_length, container);
            WriteByteArray(verify_token, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["shared_secret_length"] = picojson::value((double)shared_secret_length);
            object["shared_secret"] = picojson::value("vector of " + std::to_string(shared_secret.size()) + " unsigned char");
            object["verify_token_length"] = picojson::value((double)verify_token_length);
            object["verify_token"] = picojson::value("vector of " + std::to_string(verify_token.size()) + " unsigned char");

            return value;
        }

    private:
        int shared_secret_length;
        std::vector<unsigned char> shared_secret;
        int verify_token_length;
        std::vector<unsigned char> verify_token;
    };
} // Botcraft