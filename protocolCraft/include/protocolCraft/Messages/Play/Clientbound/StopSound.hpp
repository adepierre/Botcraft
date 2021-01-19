#pragma once

#if PROTOCOL_VERSION > 342
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class StopSound : public BaseMessage<StopSound>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x4C;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x52;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x53;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x52;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x52;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Stop Sound";
        }

        void SetFlags(const char flags_)
        {
            flags = flags_;
        }

        void SetSource(const int source_)
        {
            source = source_;
        }

        void SetSound(const Identifier& sound_)
        {
            sound = sound_;
        }


        const char GetFlags() const
        {
            return flags;
        }

        const int GetSource() const
        {
            return source;
        }

        const Identifier& GetSound() const
        {
            return sound;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            flags = ReadData<char>(iter, length);
            if (flags & 0x01)
            {
                source = ReadVarInt(iter, length);
            }
            if (flags & 0x02)
            {
                sound = ReadString(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(flags, container);
            if (flags & 0x01)
            {
                WriteVarInt(source, container);
            }
            if (flags & 0x02)
            {
                WriteString(sound, container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["flags"] = picojson::value((double)flags);
            if (flags & 0x01)
            {
                object["source"] = picojson::value((double)source);
            }
            if (flags & 0x02)
            {
                object["sound"] = picojson::value(sound);
            }

            return value;
        }

    private:
        char flags;
        int source;
        Identifier sound;

    };
} //ProtocolCraft
#endif
