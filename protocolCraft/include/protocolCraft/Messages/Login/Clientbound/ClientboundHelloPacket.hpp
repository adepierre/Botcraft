#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundHelloPacket : public BaseMessage<ClientboundHelloPacket>
    {
    public:
        static constexpr int packet_id = 0x01;
        static constexpr std::string_view packet_name = "Hello";

        virtual ~ClientboundHelloPacket() override
        {

        }

        void SetServerID(const std::string& server_id_)
        {
            server_ID = server_id_;
        }

        void SetPublicKey(const std::vector<unsigned char>& public_key_)
        {
            public_key = public_key_;
        }

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        void SetNonce(const std::vector<unsigned char>& nonce_)
        {
            nonce = nonce_;
        }
#else
        void SetChallenge(const std::vector<unsigned char>& challenge_)
        {
            challenge = challenge_;
        }
#endif

#if PROTOCOL_VERSION > 764 /* > 1.20.4 */
        void SetShouldAuthenticate(const bool should_authenticate_)
        {
            should_authenticate = should_authenticate_;
        }
#endif

        const std::string& GetServerID() const
        {
            return server_ID;
        }

        const std::vector<unsigned char>& GetPublicKey() const
        {
            return public_key;
        }

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        const std::vector<unsigned char>& GetNonce() const
        {
            return nonce;
        }
#else
        const std::vector<unsigned char>& GetChallenge() const
        {
            return challenge;
        }
#endif

#if PROTOCOL_VERSION > 764 /* > 1.20.4 */
        bool GetShouldAuthenticate() const
        {
            return should_authenticate;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            server_ID = ReadData<std::string>(iter, length);
            public_key = ReadVector<unsigned char>(iter, length);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            nonce = ReadVector<unsigned char>(iter, length);
#else
            challenge = ReadVector<unsigned char>(iter, length);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.4 */
            should_authenticate = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(server_ID, container);
            WriteVector<unsigned char>(public_key, container);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            WriteVector<unsigned char>(nonce, container);
#else
            WriteVector<unsigned char>(challenge, container);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.4 */
            WriteData<bool>(should_authenticate, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["server_ID"] = server_ID;
            output["public_key"] = "vector of " + std::to_string(public_key.size()) + " unsigned char";
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            output["nonce"] = "vector of " + std::to_string(nonce.size()) + " unsigned char";
#else
            output["challenge"] = "vector of " + std::to_string(challenge.size()) + " unsigned char";
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.4 */
            output["should_authenticate"] = should_authenticate;
#endif

            return output;
        }

    private:
        std::string server_ID;
        std::vector<unsigned char> public_key;
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        std::vector<unsigned char> nonce;
#else
        std::vector<unsigned char> challenge;
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.4 */
        bool should_authenticate = false;
#endif
    };
}
