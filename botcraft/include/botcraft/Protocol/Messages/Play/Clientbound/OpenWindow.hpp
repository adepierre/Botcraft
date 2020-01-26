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
            return 0x2E;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x2F;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Open Window";
        }

#if PROTOCOL_VERSION < 452
        const unsigned char GetWindowId() const
        {
            return window_id;
        }

        const std::string& GetWindowType() const
        {
            return window_type;
        }
#else
		const int GetWindowId() const
		{
			return window_id;
		}

		const int GetWindowType() const
		{
			return window_type;
		}
#endif

        const Chat& GetWindowTitle() const
        {
            return window_title;
        }

#if PROTOCOL_VERSION < 452
        const unsigned char GetNumberOfSlots() const
        {
            return number_of_slots;
        }

        const int GetEntityId() const
        {
            return entity_id;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
#if PROTOCOL_VERSION < 452
            window_id = ReadData<unsigned char>(iter, length);
            window_type = ReadString(iter, length);
            window_title.Read(iter, length);
            number_of_slots = ReadData<unsigned char>(iter, length);
            if (window_type == "EntityHorse")
            {
                entity_id = ReadData<int>(iter, length);
            }
#else
			window_id = ReadVarInt(iter, length);
			window_type = ReadVarInt(iter, length);
			window_title.Read(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            std::cerr << "Clientbound message" << std::endl;
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

#if PROTOCOL_VERSION < 452
            object["window_id"] = picojson::value((double)window_id);
            object["window_type"] = picojson::value(window_type);
            object["number_of_slots"] = picojson::value((double)number_of_slots);
            object["entity_id"] = picojson::value((double)entity_id);
#else
            object["window_id"] = picojson::value((double)window_id);
            object["window_type"] = picojson::value((double)window_type);
#endif

            object["window_title"] = window_title.Serialize();

            return value;
        }

    private:
#if PROTOCOL_VERSION < 452
        unsigned char window_id;
		std::string window_type;
		unsigned char number_of_slots;
		int entity_id;
#else
		int window_id;
		int window_type;
#endif
		Chat window_title;
    };
} //Botcraft