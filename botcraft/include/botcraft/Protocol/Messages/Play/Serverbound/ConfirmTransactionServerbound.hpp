#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
{
    class ConfirmTransactionServerbound : public BaseMessage<ConfirmTransactionServerbound>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x05;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x06;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x07;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575
			return 0x07;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Confirm Transaction (serverbound)";
        }

        void SetWindowId(const char c)
        {
            window_id = c;
        }

        void SetActionNumber(const short s)
        {
            action_number = s;
        }

        void SetAccepted(const bool b)
        {
            accepted = b;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            std::cerr << "Severbound message" << std::endl;
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<char>(window_id, container);
            WriteData<short>(action_number, container);
            WriteData<bool>(accepted, container);
        }

    private:
        char window_id;
        short action_number;
        bool accepted;
    };
} //Botcraft