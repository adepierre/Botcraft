#pragma once

#if PROTOCOL_VERSION > 451
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class OpenHorseWindow : public BaseMessage<OpenHorseWindow>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1F;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x20;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Open Horse Window";
        }

        void SetWindowId(const char window_id_)
        {
            window_id = window_id_;
        }

        void SetNumberOfSlots(const int number_of_slots_)
        {
            number_of_slots = number_of_slots_;
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }


        const char GetWindowId() const
        {
            return window_id;
        }

        const int GetNumberOfSlots() const
        {
            return number_of_slots;
        }

        const int GetEntityId() const
        {
            return entity_id;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            window_id = ReadData<char>(iter, length);
            number_of_slots = ReadVarInt(iter, length);
            entity_id = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(window_id, container);
            WriteVarInt(number_of_slots, container);
            WriteData<int>(entity_id, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["window_id"] = picojson::value((double)window_id);
            object["number_of_slots"] = picojson::value((double)number_of_slots);
            object["entity_id"] = picojson::value((double)entity_id);

            return value;
        }

    private:
        char window_id;
        int number_of_slots;
        int entity_id;

    };
} //ProtocolCraft
#endif
