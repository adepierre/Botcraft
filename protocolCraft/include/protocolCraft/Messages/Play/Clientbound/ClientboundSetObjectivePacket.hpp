#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 389 /* > 1.12.2 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Types/Chat/NumberFormat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSetObjectivePacket : public BaseMessage<ClientboundSetObjectivePacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x42;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x45;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x49;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */ || PROTOCOL_VERSION == 735 /* 1.16 */ ||  \
      PROTOCOL_VERSION == 736 /* 1.16.1 */ || PROTOCOL_VERSION == 751 /* 1.16.2 */ ||  \
      PROTOCOL_VERSION == 753 /* 1.16.3 */ || PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x4A;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */ ||  \
      PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x53;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x56;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x54;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x58;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x5A;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x5C;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Objective";

        virtual ~ClientboundSetObjectivePacket() override
        {

        }

        void SetObjectiveName(const std::string& objective_name_)
        {
            objective_name = objective_name_;
        }

#if PROTOCOL_VERSION < 390 /* < 1.13 */
        void SetDisplayName(const std::string& display_name_)
#else
        void SetDisplayName(const Chat& display_name_)
#endif
        {
            display_name = display_name_;
        }

#if PROTOCOL_VERSION < 349 /* < 1.13 */
        void SetRenderType(const std::string& render_type_)
#else
        void SetRenderType(const int render_type_)
#endif
        {
            render_type = render_type_;
        }

        void SetMethod(const char method_)
        {
            method = method_;
        }

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        void SetNumberFormat(const NumberFormat& number_format_)
        {
            number_format = number_format_;
        }
#endif


        const std::string& GetObjectiveName() const
        {
            return objective_name;
        }

#if PROTOCOL_VERSION < 390 /* < 1.13 */
        const std::string& GetSetDisplayName() const
#else
        const Chat& GetSetDisplayName() const
#endif
        {
            return display_name;
        }

#if PROTOCOL_VERSION < 349 /* < 1.13 */
        const std::string& GetRenderType() const
#else
        int GetRenderType() const
#endif
        {
            return render_type;
        }

        char GetMethod() const
        {
            return method;
        }

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        const NumberFormat& GetNumberFormat() const
        {
            return number_format;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            objective_name = ReadData<std::string>(iter, length);
            method = ReadData<char>(iter, length);
            if (method == 0 || method == 2)
            {
#if PROTOCOL_VERSION < 390 /* < 1.13 */
                display_name = ReadData<std::string>(iter, length);
#else
                display_name = ReadData<Chat>(iter, length);
#endif
#if PROTOCOL_VERSION < 349 /* < 1.13 */
                render_type = ReadData<std::string>(iter, length);
#else
                render_type = ReadData<VarInt>(iter, length);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
                number_format = ReadData<NumberFormat>(iter, length);
#endif
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(objective_name, container);
            WriteData<char>(method, container);
            if (method == 0 || method == 2)
            {
#if PROTOCOL_VERSION < 390 /* < 1.13 */
                WriteData<std::string>(display_name, container);
#else
                WriteData<Chat>(display_name, container);
#endif
#if PROTOCOL_VERSION < 349 /* < 1.13 */
                WriteData<std::string>(render_type, container);
#else
                WriteData<VarInt>(render_type, container);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
                WriteData<NumberFormat>(number_format, container);
#endif
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["objective_name"] = objective_name;
            output["method"] = method;
            if (method == 0 || method == 2)
            {
                output["display_name"] = display_name;
                output["render_type"] = render_type;
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
                output["number_format"] = number_format;
#endif
            }

            return output;
        }

    private:
        std::string objective_name;
#if PROTOCOL_VERSION < 390 /* < 1.13 */
        std::string display_name;
#else
        Chat display_name;
#endif
#if PROTOCOL_VERSION < 349 /* < 1.13 */
        std::string render_type;
#else
        int render_type = 0;
#endif
        char method = 0;
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        NumberFormat number_format;
#endif
    };
} //ProtocolCraft
