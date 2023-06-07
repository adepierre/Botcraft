#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 389
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSetObjectivePacket : public BaseMessage<ClientboundSetObjectivePacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x42;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x45;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x49;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x4A;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x4A;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x4A;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x53;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x53;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x53;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x56;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x54;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x58;
#elif PROTOCOL_VERSION == 763 // 1.20
        static constexpr int packet_id = 0x58;
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

#if PROTOCOL_VERSION < 390
        void SetDisplayName(const std::string& display_name_)
#else
        void SetDisplayName(const Chat& display_name_)
#endif
        {
            display_name = display_name_;
        }

#if PROTOCOL_VERSION < 349
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


        const std::string& GetObjectiveName() const
        {
            return objective_name;
        }

#if PROTOCOL_VERSION < 390
        const std::string& GetSetDisplayName() const
#else
        const Chat& GetSetDisplayName() const
#endif
        {
            return display_name;
        }

#if PROTOCOL_VERSION < 349
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


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            objective_name = ReadData<std::string>(iter, length);
            method = ReadData<char>(iter, length);
            if (method == 0 || method == 2)
            {
#if PROTOCOL_VERSION < 390
                display_name = ReadData<std::string>(iter, length);
#else
                display_name = ReadData<Chat>(iter, length);
#endif
#if PROTOCOL_VERSION < 349
                render_type = ReadData<std::string>(iter, length);
#else
                render_type = ReadData<VarInt>(iter, length);
#endif
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(objective_name, container);
            WriteData<char>(method, container);
            if (method == 0 || method == 2)
            {
#if PROTOCOL_VERSION < 390
                WriteData<std::string>(display_name, container);
#else
                WriteData<Chat>(display_name, container);
#endif
#if PROTOCOL_VERSION < 349
                WriteData<std::string>(render_type, container);
#else
                WriteData<VarInt>(render_type, container);
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
            }

            return output;
        }

    private:
        std::string objective_name;
#if PROTOCOL_VERSION < 390
        std::string display_name;
#else
        Chat display_name;
#endif
#if PROTOCOL_VERSION < 349
        std::string render_type;
#else
        int render_type;
#endif
        char method;
    };
} //ProtocolCraft
