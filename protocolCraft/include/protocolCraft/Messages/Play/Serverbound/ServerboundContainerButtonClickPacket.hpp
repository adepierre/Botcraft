#pragma once

#if PROTOCOL_VERSION > 476
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundContainerButtonClickPacket : public BaseMessage<ServerboundContainerButtonClickPacket>
    {
    public:
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x0A;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x09;
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


        const char GetContainerId() const
        {
            return container_id;
        }

        const char GetButtonId() const
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

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["container_id"] = container_id;
            output["button_id"] = button_id;

            return output;
        }

    private:
        char container_id;
        char button_id;

    };
} //ProtocolCraft
#endif
