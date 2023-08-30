#pragma once

#if PROTOCOL_VERSION > 476
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundContainerButtonClickPacket : public BaseMessage<ServerboundContainerButtonClickPacket>
    {
    public:
#if   PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498 || PROTOCOL_VERSION == 573 ||  \
      PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 ||  \
      PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x0A;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x0A;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Container Button Click";

        virtual ~ServerboundContainerButtonClickPacket() override
        {

        }

        void SetContainerId(const char container_id_)
        {
            container_id = container_id_;
        }

        void SetButtonId(const char button_id_)
        {
            button_id = button_id_;
        }


        char GetContainerId() const
        {
            return container_id;
        }

        char GetButtonId() const
        {
            return button_id;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            container_id = ReadData<char>(iter, length);
            button_id = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(container_id, container);
            WriteData<char>(button_id, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["container_id"] = container_id;
            output["button_id"] = button_id;

            return output;
        }

    private:
        char container_id = 0;
        char button_id = 0;

    };
} //ProtocolCraft
#endif
