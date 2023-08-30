#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ServerboundSeenAdvancementsPacket : public BaseMessage<ServerboundSeenAdvancementsPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498 || PROTOCOL_VERSION == 573 ||  \
      PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736
        static constexpr int packet_id = 0x21;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754 || PROTOCOL_VERSION == 755 ||  \
      PROTOCOL_VERSION == 756 || PROTOCOL_VERSION == 757 ||  \
      PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 760 || PROTOCOL_VERSION == 761 ||  \
      PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x25;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Seen Advancement";

        virtual ~ServerboundSeenAdvancementsPacket() override
        {

        }

        void SetAction(const int action_)
        {
            action = action_;
        }

        void SetTab(const Identifier& tab_)
        {
            tab = tab_;
        }


        int GetAction() const
        {
            return action;
        }

        const Identifier& GetTab() const
        {
            return tab;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            action = ReadData<VarInt>(iter, length);
            if (action == 0)
            {
                tab = ReadData<Identifier>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(action, container);
            if (action == 0)
            {
                WriteData<Identifier>(tab, container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["action"] = action;
            if (action == 0)
            {
                output["tab"] = tab;
            }

            return output;
        }

    private:
        int action = 0;
        Identifier tab;

    };
} //ProtocolCraft
