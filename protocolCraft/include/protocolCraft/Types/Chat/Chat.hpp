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
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            raw_text = ReadData<std::string>(iter, length);
            
            text = ParseChat(Json::Parse(raw_text));
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(raw_text, container);
        }

        std::string ParseChat(const Json::Value& raw_json);

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["raw_text"] = raw_text;

            return output;
        }

    private:
        std::string text;
        std::string raw_text;
    };
}
