#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundHelloPacket : public BaseMessage<ServerboundHelloPacket>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x00;
        }

        virtual const std::string GetName() const override
        {
            return "Hello";
        }

        virtual ~ServerboundHelloPacket() override
        {

        }

        void SetGameProfile(const std::string &n)
        {
            game_profile = n;
        }

        const std::string& GetGameProfile() const
        {
            return game_profile;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            game_profile = ReadString(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteString(game_profile, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["game_profile"] = picojson::value(game_profile);

            return value;
        }

    private:
        std::string game_profile;
    };
} // Botcraft