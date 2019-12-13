#pragma once

#include <iostream>

#include "botcraft/Game/Inventory/Slot.hpp"

#include "botcraft/Protocol/BaseMessage.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
{
    class WindowItems : public BaseMessage<WindowItems>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x14;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x15;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x14;
#elif PROTOCOL_VERSION == 573
			return 0x15;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Window Items";
        }

        const unsigned char GetWindowId() const
        {
            return window_id;
        }

        const short GetCount() const
        {
            return count;
        }

        const std::vector<Slot>& GetSlotData() const
        {
            return slot_data;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            window_id = ReadData<unsigned char>(iter, length);
            count = ReadData<short>(iter, length);
            slot_data = std::vector<Slot>(count);
            for (int i = 0; i < count; ++i)
            {
                slot_data[i].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            std::cerr << "Clientbound message" << std::endl;
        }

    private:
        unsigned char window_id;
        short count;
        std::vector<Slot> slot_data;
    };
} //Botcraft