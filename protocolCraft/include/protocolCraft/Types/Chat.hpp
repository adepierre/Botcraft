#pragma once

#include <string>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class Chat : public NetworkType
    {
    public:
        void SetText(const std::string &s)
        {
            text = s;
        }

        void SetFrom(const std::string &s)
        {
            from = s;
        }

        const std::string& GetText() const
        {
            return text;
        }

        const std::string& GetFrom() const
        {
            return from;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            const std::string json = ReadString(iter, length);
            
            from = "";
            text = ParseChat(json);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteString(text, container);
        }

        const std::string ParseChat(const std::string &json);

        virtual const picojson::value SerializeImpl() const override;

    private:
        std::string text;
        std::string from;
    };
}