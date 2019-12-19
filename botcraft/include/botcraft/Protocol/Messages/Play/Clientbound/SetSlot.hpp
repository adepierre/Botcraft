#pragma once

#include <iostream>
#include <string>

#include "botcraft/Protocol/BaseMessage.hpp"
#include "botcraft/Game/Inventory/Slot.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
{
    class SetSlot : public BaseMessage<SetSlot>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x16;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x17;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x16;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575
			return 0x17;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Slot";
        }

        const char GetWindowId() const
        {
            return window_id;
        }

        const short GetSlot() const
        {
            return slot;
        }

        const Slot& GetSlotData() const
        {
            return slot_data;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            window_id = ReadData<char>(iter, length);
            slot = ReadData<short>(iter, length);
            slot_data.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            std::cerr << "Clientbound message" << std::endl;
        }

    private:
        char window_id;
        short slot;
        Slot slot_data;

    };
} //Botcraft