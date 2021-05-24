#pragma once

#if PROTOCOL_VERSION > 342
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundStopSoundPacket : public BaseMessage<ClientboundStopSoundPacket>
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

        virtual ~ClientboundStopSoundPacket() override
        {

        }

        void SetSource(const int source_)
        {
            source = source_;
        }

        void SetName_(const Identifier& name__)
        {
            name_ = name__;
        }


        const int GetSource() const
        {
            return source;
        }

        const Identifier& GetName_() const
        {
            return name_;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            char flags = ReadData<char>(iter, length);
            if (flags & 0x01)
            {
                source = ReadVarInt(iter, length);
            }
            if (flags & 0x02)
            {
                name_.Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(((!name_.GetName().empty()) << 1) | (source != -1), container);
            if (source != -1)
            {
                WriteVarInt((int)source, container);
            }
            if (!name_.GetName().empty())
            {
                name_.Write(container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();


            if (source != -1)
            {
                object["source"] = picojson::value((double)source);
            }
            if (!name_.GetName().empty())
            {
                object["name_"] = name_.Serialize();
            }

            return value;
        }

    private:
        int source = -1;
        Identifier name_;

    };
} //ProtocolCraft
#endif
