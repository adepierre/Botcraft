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

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            raw_text = ReadData<std::string>(iter, length);
            
            text = ParseChat(nlohmann::json::parse(raw_text));
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<std::string>(raw_text, container);
        }

        const std::string ParseChat(const nlohmann::json& raw_json);

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["raw_text"] = raw_text;

            return output;
        }

    private:
        std::string text;
        std::string raw_text;
    };
}
