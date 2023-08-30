#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundSetDisplayObjectivePacket : public BaseMessage<ClientboundSetDisplayObjectivePacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x39;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x3E;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x42;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578 || PROTOCOL_VERSION == 735 ||  \
      PROTOCOL_VERSION == 736 || PROTOCOL_VERSION == 751 ||  \
      PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x43;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 ||  \
      PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x4C;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x4F;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x4D;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x51;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Display Objective";

        virtual ~ClientboundSetDisplayObjectivePacket() override
        {

        }

        void SetSlot(const char slot_)
        {
            slot = slot_;
        }

        void SetObjectiveName(const std::string& objective_name_)
        {
            objective_name = objective_name_;
        }


        char GetSlot() const
        {
            return slot;
        }

        const std::string& GetObjectiveName() const
        {
            return objective_name;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            slot = ReadData<char>(iter, length);
            objective_name = ReadData<std::string>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(slot, container);
            WriteData<std::string>(objective_name, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["slot"] = slot;
            output["objective_name"] = objective_name;

            return output;
        }

    private:
        char slot = 0;
        std::string objective_name;

    };
} //ProtocolCraft
