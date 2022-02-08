#pragma once

#include <string>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class Chat : public NetworkType
    {
    public:
        virtual ~Chat() override
        {

        }

        void SetText(const std::string& s)
        {
            text = s;
        }

        void SetFrom(const std::string& s)
        {
            from = s;
        }

        void SetRawText(const std::string& s)
        {
            raw_text = s;
        }

        const std::string& GetText() const
        {
            return text;
        }

        const std::string& GetRawText() const
        {
            return raw_text;
        }

        const std::string& GetFrom() const
        {
            return from;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            raw_text = ReadData<std::string>(iter, length);
            
            from = "";
            text = ParseChat(raw_text);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(raw_text, container);
        }

        // Parses the message JSON and extracts message data
        std::string ParseChat(const std::string& json);
        // used for recursive parsing of sub messages
        std::string ParseChat(const nlohmann::json&);

        virtual const nlohmann::json SerializeImpl() const override;

    private:
        std::string text;
        std::string from;
        std::string raw_text;
    };
}