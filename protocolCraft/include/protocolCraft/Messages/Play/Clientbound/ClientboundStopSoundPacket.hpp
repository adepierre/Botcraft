#pragma once

#if PROTOCOL_VERSION > 342
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundStopSoundPacket : public BaseMessage<ClientboundStopSoundPacket>
    {
    public:
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x4C;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x52;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x53;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x52;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x52;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x5D;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x5E;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x5E;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x61;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x5F;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Stop Sound";

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
                source = ReadData<VarInt>(iter, length);
            }
            if (flags & 0x02)
            {
                name_ = ReadData<Identifier>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(((!name_.GetName().empty()) << 1) | (source != -1), container);
            if (source != -1)
            {
                WriteData<VarInt>(source, container);
            }
            if (!name_.GetName().empty())
            {
                WriteData<Identifier>(name_, container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;


            if (source != -1)
            {
                output["source"] = source;
            }
            if (!name_.GetName().empty())
            {
                output["name_"] = name_.Serialize();
            }

            return output;
        }

    private:
        int source = -1;
        Identifier name_;

    };
} //ProtocolCraft
#endif
