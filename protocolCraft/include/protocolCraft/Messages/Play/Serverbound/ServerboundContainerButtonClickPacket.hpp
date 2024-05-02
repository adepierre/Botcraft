#pragma once

#if PROTOCOL_VERSION > 476 /* > 1.13.2 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundContainerButtonClickPacket : public BaseMessage<ServerboundContainerButtonClickPacket>
    {
    public:
#if   PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */ ||  \
      PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x0A;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x0A;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 766 /* 1.20.5 */
        static constexpr int packet_id = 0x0D;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Container Button Click";

        virtual ~ServerboundContainerButtonClickPacket() override
        {

        }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        void SetContainerId(const char container_id_)
        {
            container_id = container_id_;
        }

        void SetButtonId(const char button_id_)
        {
            button_id = button_id_;
        }
#else
        void SetContainerId(const int container_id_)
        {
            container_id = container_id_;
        }

        void SetButtonId(const int button_id_)
        {
            button_id = button_id_;
        }
#endif


#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        char GetContainerId() const
        {
            return container_id;
        }

        char GetButtonId() const
        {
            return button_id;
        }
#else
        int GetContainerId() const
        {
            return container_id;
        }

        int GetButtonId() const
        {
            return button_id;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            container_id = ReadData<char>(iter, length);
            button_id = ReadData<char>(iter, length);
#else
            container_id = ReadData<VarInt>(iter, length);
            button_id = ReadData<VarInt>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            WriteData<char>(container_id, container);
            WriteData<char>(button_id, container);
#else
            WriteData<VarInt>(container_id, container);
            WriteData<VarInt>(button_id, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["container_id"] = container_id;
            output["button_id"] = button_id;

            return output;
        }

    private:
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        char container_id = 0;
        char button_id = 0;
#else
        int container_id = 0;
        int button_id = 0;
#endif
    };
} //ProtocolCraft
#endif
