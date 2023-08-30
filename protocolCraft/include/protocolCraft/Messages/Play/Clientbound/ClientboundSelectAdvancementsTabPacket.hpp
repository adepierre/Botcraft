#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSelectAdvancementsTabPacket : public BaseMessage<ClientboundSelectAdvancementsTabPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x37;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x3A;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x3C;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x3D;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x3C;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x40;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x3E;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x41;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x40;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x44;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Select Advancement Tab";

        virtual ~ClientboundSelectAdvancementsTabPacket() override
        {

        }

        void SetTab(const std::optional<std::string>& tab_)
        {
            tab = tab_;
        }


        const std::optional<std::string>& GetTab() const
        {
            return tab;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            tab = ReadOptional<std::string>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteOptional<std::string>(tab, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            if (tab.has_value())
            {
                output["tab"] = tab.value();
            }

            return output;
        }

    private:
        std::optional<std::string> tab;

    };
} //ProtocolCraft
