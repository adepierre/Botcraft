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
            game_profile = ReadData<std::string>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<std::string>(game_profile, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["game_profile"] = game_profile;

            return output;
        }

    private:
        std::string game_profile;
    };
} // Botcraft