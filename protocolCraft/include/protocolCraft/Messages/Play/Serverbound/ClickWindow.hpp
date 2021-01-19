#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class ClickWindow : public BaseMessage<ClickWindow>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x07;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x08;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x09;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x09;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x09;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x09;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Click Window";
        }

        void SetWindowId(const unsigned char window_id_)
        {
            window_id = window_id_;
        }

        void SetSlot(const short slot_)
        {
            slot = slot_;
        }

        void SetButton(const char button_)
        {
            button = button_;
        }

        void SetActionNumber(const short action_number_)
        {
            action_number = action_number_;
        }

        void SetMode(const int mode_)
        {
            mode = mode_;
        }

        void SetClickedItem(const Slot& clicked_item_)
        {
            clicked_item = clicked_item_;
        }


        const unsigned char GetWindowId() const
        {
            return window_id;
        }

        const short GetSlot() const
        {
            return slot;
        }

        const char GetButton() const
        {
            return button;
        }

        const short GetActionNumber() const
        {
            return action_number;
        }

        const int GetMode() const
        {
            return mode;
        }

        const Slot& GetClickedItem() const
        {
            return clicked_item;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            window_id = ReadData<unsigned char>(iter, length);
            slot = ReadData<short>(iter, length);
            button = ReadData<char>(iter, length);
            action_number = ReadData<short>(iter, length);
            mode = ReadVarInt(iter, length);
            clicked_item.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<unsigned char>(window_id, container);
            WriteData<short>(slot, container);
            WriteData<char>(button, container);
            WriteData<short>(action_number, container);
            WriteVarInt(mode, container);
            clicked_item.Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["window_id"] = picojson::value((double)window_id);
            object["slot"] = picojson::value((double)slot);
            object["button"] = picojson::value((double)button);
            object["action_number"] = picojson::value((double)action_number);
            object["mode"] = picojson::value((double)mode);
            object["clicked_item"] = clicked_item.Serialize();

            return value;
        }

    private:
        unsigned char window_id;
        short slot;
        char button;
        short action_number;
        int mode;
        Slot clicked_item;

    };
} //ProtocolCraft