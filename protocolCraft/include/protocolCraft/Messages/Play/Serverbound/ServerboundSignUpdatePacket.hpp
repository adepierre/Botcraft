#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

#include <array>

namespace ProtocolCraft
{
    class ServerboundSignUpdatePacket : public BaseMessage<ServerboundSignUpdatePacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x26;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x2A;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x2D;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 763 // 1.20
        static constexpr int packet_id = 0x2E;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Sign Update";

        virtual ~ServerboundSignUpdatePacket() override
        {

        }

        void SetPos(const NetworkPosition& pos_)
        {
            pos = pos_;
        }

#if PROTOCOL_VERSION > 762
        void SetIsFrontText(const bool is_front_text_)
        {
            is_front_text = is_front_text_;
        }
#endif

        void SetLines(const std::array<std::string, 4>& lines_)
        {
            lines = lines_;
        }


        const NetworkPosition& GetPos() const
        {
            return pos;
        }

#if PROTOCOL_VERSION > 762
        bool GetIsFrontText() const
        {
            return is_front_text;
        }
#endif

        const std::array<std::string, 4>& GetLines() const
        {
            return lines;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            pos = ReadData<NetworkPosition>(iter, length);
#if PROTOCOL_VERSION > 762
            is_front_text = ReadData<bool>(iter, length);
#endif
            lines = std::array<std::string, 4>();
            for (int i = 0; i < 4; ++i)
            {
                lines[i] = ReadData<std::string>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<NetworkPosition>(pos, container);
#if PROTOCOL_VERSION > 762
            WriteData<bool>(is_front_text, container);
#endif
            for (int i = 0; i < 4; ++i)
            {
                WriteData<std::string>(lines[i], container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["pos"] = pos;
#if PROTOCOL_VERSION > 762
            output["is_front_text"] = is_front_text;
#endif
            output["lines"] = lines;

            return output;
        }

    private:
        NetworkPosition pos;
#if PROTOCOL_VERSION > 762
        bool is_front_text = false;
#endif
        std::array<std::string, 4> lines;

    };
} //ProtocolCraft
