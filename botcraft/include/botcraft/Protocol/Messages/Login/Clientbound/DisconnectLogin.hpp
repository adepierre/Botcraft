#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"
#include "botcraft/Protocol/Types/Chat.hpp"

namespace Botcraft
{
    class DisconnectLogin : public BaseMessage<DisconnectLogin>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x00;
        }

        virtual const std::string GetName() const override
        {
            return "Disconnect (login)";
        }

        const Chat& GetReason() const
        {
            return reason;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            reason.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            std::cerr << "Clientbound message" << std::endl;
        }

    private:
        Chat reason;
    };
}