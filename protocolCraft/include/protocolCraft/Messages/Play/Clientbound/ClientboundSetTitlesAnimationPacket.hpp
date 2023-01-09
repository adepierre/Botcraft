#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetTitlesAnimationPacket : public BaseMessage<ClientboundSetTitlesAnimationPacket>
    {
    public:
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x5A;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x5B;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x5B;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x5E;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x5C;
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
        int fade_in;
        int stay;
        int fade_out;

    };
} //ProtocolCraft
#endif
