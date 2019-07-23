#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
{
    class ConfirmTransactionClientbound : public BaseMessage<ConfirmTransactionClientbound>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x11;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x12;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x12;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Confirm Transaction (clientbound)";
        }

        const char GetWindowId() const
        {
            return window_id;
        }

        const short GetActionNumber() const
        {
            return action_number;
        }

        const bool GetAccepted() const
        {
            return accepted;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            window_id = ReadData<char>(iter, length);
            action_number = ReadData<short>(iter, length);
            accepted = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            std::cerr << "Clientbound message" << std::endl;
        }

    private:
        char window_id;
        short action_number;
        bool accepted;
    };
} //Botcraft