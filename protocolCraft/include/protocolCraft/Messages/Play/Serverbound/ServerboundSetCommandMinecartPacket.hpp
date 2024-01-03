#pragma once

#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundSetCommandMinecartPacket : public BaseMessage<ServerboundSetCommandMinecartPacket>
    {
    public:
#if   PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x25;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x26;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */ || PROTOCOL_VERSION == 755 /* 1.17 */ ||  \
      PROTOCOL_VERSION == 756 /* 1.17.1 */ || PROTOCOL_VERSION == 757 /* 1.18/.1 */ ||  \
      PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */ || PROTOCOL_VERSION == 761 /* 1.19.3 */ ||  \
      PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x2A;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x2D;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x2E;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Command Minecart";

        virtual ~ServerboundSetCommandMinecartPacket() override
        {

        }

        void SetEntity(const int entity_)
        {
            entity = entity_;
        }

        void SetCommand(const std::string& command_)
        {
            command = command_;
        }

        void SetTrackOutput(const bool track_output_)
        {
            track_output = track_output_;
        }


        int GetEntity() const
        {
            return entity;
        }

        const std::string& GetCommand() const
        {
            return command;
        }

        bool GetTrackOutput() const
        {
            return track_output;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity = ReadData<VarInt>(iter, length);
            command = ReadData<std::string>(iter, length);
            track_output = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(entity, container);
            WriteData<std::string>(command, container);
            WriteData<bool>(track_output, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["entity"] = entity;
            output["command"] = command;
            output["track_output"] = track_output;

            return output;
        }

    private:
        int entity = 0;
        std::string command;
        bool track_output = false;

    };
} //ProtocolCraft
#endif
