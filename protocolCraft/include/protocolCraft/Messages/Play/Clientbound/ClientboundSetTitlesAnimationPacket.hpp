#pragma once

#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetTitlesAnimationPacket : public BaseMessage<ClientboundSetTitlesAnimationPacket>
    {
    public:
#if   PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */
        static constexpr int packet_id = 0x5A;
#elif PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */ ||  \
      PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x5B;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x5E;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x5C;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x60;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x62;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x64;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x66;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Titles Animation";

        virtual ~ClientboundSetTitlesAnimationPacket() override
        {

        }


        void SetFadeIn(const int fade_in_)
        {
            fade_in = fade_in_;
        }

        void SetStay(const int stay_)
        {
            stay= stay_;
        }

        void SetFadeOut(const int fade_out_)
        {
            fade_out= fade_out_;
        }


        int GetFadeIn() const
        {
            return fade_in;
        }

        int GetStay() const
        {
            return stay;
        }

        int GetFadeOut() const
        {
            return fade_out;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            fade_in = ReadData<int>(iter, length);
            stay = ReadData<int>(iter, length);
            fade_out = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<int>(fade_in, container);
            WriteData<int>(stay, container);
            WriteData<int>(fade_out, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["fade_in"] = fade_in;
            output["stay"] = stay;
            output["fade_out"] = fade_out;

            return output;
        }

    private:
        int fade_in = 0;
        int stay = 0;
        int fade_out = 0;

    };
} //ProtocolCraft
#endif
