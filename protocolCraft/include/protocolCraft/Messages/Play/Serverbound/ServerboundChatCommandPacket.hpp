#if PROTOCOL_VERSION > 758
#pragma once

#include <string>
#include <map>
#include <vector>

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundChatCommandPacket : public BaseMessage<ServerboundChatCommandPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 759 // 1.19
            return 0x03;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Chat Command";
        }

        virtual ~ServerboundChatCommandPacket() override
        {

        }

        void SetCommand(const std::string& command_)
        {
            command = command_;
        }

        void SetTimestamp(const long long int timestamp_)
        {
            timestamp = timestamp_;
        }

        void SetSalt(const long long int salt_)
        {
            salt = salt_;
        }

        void SetSignatures(const std::map<std::string, std::vector<unsigned char> >& signatures_)
        {
            signatures = signatures_;
        }

        void SetSignedPreview(const bool signed_preview_)
        {
            signed_preview = signed_preview_;
        }


        const std::string& GetCommand() const
        {
            return command;
        }

        const long long int GetTimestamp() const
        {
            return timestamp;
        }

        const long long int GetSalt() const
        {
            return salt;
        }

        const std::map<std::string, std::vector<unsigned char> >& GetSignatures() const
        {
            return signatures;
        }

        const bool GetSignedPreview() const
        {
            return signed_preview;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            command = ReadData<std::string>(iter, length);
            timestamp = ReadData<long long int>(iter, length);
            salt = ReadData<long long int>(iter, length);
            const int signatures_size = ReadData<VarInt>(iter, length);
            for (int i = 0; i < signatures_size; ++i)
            {
                const std::string key = ReadData<std::string>(iter, length);
                const int value_size = ReadData<VarInt>(iter, length);
                signatures[key] = ReadByteArray(iter, length, value_size);
            }
            signed_preview = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<std::string>(command, container);
            WriteData<long long int>(timestamp, container);
            WriteData<long long int>(salt, container);
            WriteData<VarInt>(signatures.size(), container);
            for (const auto& s: signatures)
            {
                WriteData<std::string>(s.first, container);
                WriteData<VarInt>(s.second.size(), container);
                WriteByteArray(s.second, container);
            }
            WriteData<bool>(signed_preview, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["command"] = command;
            output["timestamp"] = timestamp;
            output["salt"] = salt;
            output["signatures"] = nlohmann::json();
            for (const auto& s: signatures)
            {
                output["signature"][s.first] = "Vector of " + std::to_string(s.second.size()) + " unsigned char";
                output.push_back(s);
            }
            output["signed_preview"] = signed_preview;


            return output;
        }

    private:
        std::string command;
        long long int timestamp;
        long long int salt;
        std::map<std::string, std::vector<unsigned char> > signatures;
        bool signed_preview;
    };
} //ProtocolCraft
#endif
