#pragma once

#include <iostream>

#include "botcraft/Protocol/Types/Chat.hpp"

#include "botcraft/Protocol/BaseMessage.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
{
    class OpenWindow : public BaseMessage<OpenWindow>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x13;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x14;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x13;
#elif PROTOCOL_VERSION == 573
			return 0x2F;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Open Window";
        }

        const unsigned char GetWindowId() const
        {
            return window_id;
        }

        const std::string& GetWindowType() const
        {
            return window_type;
        }

        const Chat& GetWindowTitle() const
        {
            return window_title;
        }

        const unsigned char GetNumberOfSlots() const
        {
            return number_of_slots;
        }

        const int GetEntityId() const
        {
            return entity_id;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            window_id = ReadData<unsigned char>(iter, length);
            window_type = ReadString(iter, length);
            window_title.Read(iter, length);
            number_of_slots = ReadData<unsigned char>(iter, length);
            if (window_type == "EntityHorse")
            {
                entity_id = ReadData<int>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            std::cerr << "Clientbound message" << std::endl;
        }

    private:
        unsigned char window_id;
        std::string window_type;
        Chat window_title;
        unsigned char number_of_slots;
        int entity_id;
    };
} //Botcraft