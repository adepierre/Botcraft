#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundOpenScreenPacket : public BaseMessage<ClientboundOpenScreenPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Open Screen";

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        DECLARE_FIELDS(
            (unsigned char, std::string, Chat,  unsigned char, int),
            (ContainerId,   Type,        Title, NumberOfSlots, Id_)
        );
#else
        DECLARE_FIELDS(
            (VarInt,      VarInt, Chat),
            (ContainerId, Type,   Title)
        );
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
