#pragma once

#include <string>

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
#include "protocolCraft/NetworkType.hpp"
#else
#include "protocolCraft/Types/NBT/Tag.hpp"
#endif

namespace ProtocolCraft
{
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
    class Chat : public NetworkType
#else
    class Chat : public NBT::Tag
#endif
    {
    public:
        virtual ~Chat() override
        {

        }

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        void SetRawText(const std::string& s)
        {
            raw_text = s;
        }
#endif

        const std::string& GetText() const
        {
            return text;
        }

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        const std::string& GetRawText() const
        {
            return raw_text;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
            raw_text = ReadData<std::string>(iter, length);
            text = ParseChat(Json::Parse(raw_text));
#else
            NBT::Tag::ReadUnnamedImpl(iter, length);
            text = ParseChat(*this);
#endif

        }

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(raw_text, container);
        }
#endif

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        std::string ParseChat(const Json::Value& raw_json);
#else
        std::string ParseChat(const NBT::Tag& raw);
#endif

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["raw_text"] = raw_text;

            return output;
        }
#endif

    private:
        std::string text;
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        std::string raw_text;
#endif
    };
}
