#pragma once

#if PROTOCOL_VERSION > 342 /* > 1.12.2 */
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundStopSoundPacket : public BaseMessage<ClientboundStopSoundPacket>
    {
    public:
#if   PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x4C;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x52;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x53;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x52;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */
        static constexpr int packet_id = 0x5D;
#elif PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */ ||  \
      PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x5E;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x61;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x5F;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x63;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x66;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x68;
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


        int GetSource() const
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

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;


            if (source != -1)
            {
                output["source"] = source;
            }
            if (!name_.GetName().empty())
            {
                output["name_"] = name_;
            }

            return output;
        }

    private:
        int source = -1;
        Identifier name_;

    };
} //ProtocolCraft
#endif
