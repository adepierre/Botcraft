#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
{
    class ClientStatus : public BaseMessage<ClientStatus>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x03;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x03;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x04;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Client Status";
        }

        void SetActionID(const int i)
        {
            action_id = i;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            std::cerr << "Severbound message" << std::endl;
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVarInt(action_id, container);
        }

    private:
        int action_id;
    };
} //Botcraft