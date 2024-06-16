#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundOpenScreenPacket : public BaseMessage<ClientboundOpenScreenPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x2F;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x2D;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x2D;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x2C;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x30;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x31;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x33;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Open Screen";

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        DECLARE_FIELDS_TYPES(unsigned char, std::string, Chat,  unsigned char, int);
        DECLARE_FIELDS_NAMES(ContainerId,   Type,        Title, NumberOfSlots, Id_);
#else
        DECLARE_FIELDS_TYPES(VarInt,      VarInt, Chat);
        DECLARE_FIELDS_NAMES(ContainerId, Type,   Title);
        DECLARE_READ_WRITE_SERIALIZE;
#endif

        GETTER_SETTER(ContainerId);
        GETTER_SETTER(Type);
        GETTER_SETTER(Title);
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        GETTER_SETTER(NumberOfSlots);
        GETTER_SETTER(Id_);
#endif

#if PROTOCOL_VERSION < 452 /* < 1.14 */
    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetContainerId(ReadData<unsigned char>(iter, length));
            SetType(ReadData<std::string>(iter, length));
            SetTitle(ReadData<Chat>(iter, length));
            SetNumberOfSlots(ReadData<unsigned char>(iter, length));
            if (GetType() == "EntityHorse")
            {
                SetId_(ReadData<int>(iter, length));
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<unsigned char>(GetContainerId(), container);
            WriteData<std::string>(GetType(), container);
            WriteData<Chat>(GetTitle(), container);
            WriteData<unsigned char>(GetNumberOfSlots(), container);
            if (GetType() == "EntityHorse")
            {
                WriteData<int>(GetId_(), container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::ContainerId)])] = GetContainerId();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Type)])] = GetType();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Title)])] = GetTitle();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::NumberOfSlots)])] = GetNumberOfSlots();
            if (GetType() == "EntityHorse")
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::Id_)])] = GetId_();
            }

            return output;
        }
#endif
    };
} //ProtocolCraft
