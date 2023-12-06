#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    enum class SetScoreMethod
    {
        Change = 0,
        Remove = 1
    };

    class ClientboundSetScorePacket : public BaseMessage<ClientboundSetScorePacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x45;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x48;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x4C;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */ || PROTOCOL_VERSION == 735 /* 1.16 */ ||  \
      PROTOCOL_VERSION == 736 /* 1.16.1 */ || PROTOCOL_VERSION == 751 /* 1.16.2 */ ||  \
      PROTOCOL_VERSION == 753 /* 1.16.3 */ || PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x4D;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */ ||  \
      PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x56;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x59;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x57;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x5B;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x5D;
#elif PROTOCOL_VERSION == 765 /* 1.20.3 */
        static constexpr int packet_id = 0x5F;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Score";

        virtual ~ClientboundSetScorePacket() override
        {

        }

        void SetOwner(const std::string& owner_)
        {
            owner = owner_;
        }

        void SetObjectiveName(const std::string& objective_name_)
        {
            objective_name = objective_name_;
        }

        void SetScore(const int score_)
        {
            score = score_;
        }

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        void SetMethod(const SetScoreMethod method_)
        {
            method = method_;
        }
#else
        void SetDisplay(const std::optional<Chat>& display_)
        {
            display = display_;
        }

        void SetNumberFormat(const std::optional<NumberFormat>& number_format_)
        {
            number_format = number_format_;
        }
#endif


        const std::string& GetOwner() const
        {
            return owner;
        }

        const std::string& GetObjectiveName() const
        {
            return objective_name;
        }

        int GetScore() const
        {
            return score;
        }

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        SetScoreMethod GetMethod() const
        {
            return method;
        }
#else
        const std::optional<Chat>& GetDisplay() const
        {
            return display;
        }

        const std::optional<NumberFormat>& GetNumberFormat() const
        {
            return number_format;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            owner = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
            method = static_cast<SetScoreMethod>(ReadData<char>(iter, length));
            objective_name = ReadData<std::string>(iter, length);
            if (method != SetScoreMethod::Remove)
            {
                score = ReadData<VarInt>(iter, length);
            }
#else
            objective_name = ReadData<std::string>(iter, length);
            score = ReadData<VarInt>(iter, length);
            display = ReadOptional<Chat>(iter, length);
            number_format = ReadOptional<NumberFormat>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(owner, container);
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
            WriteData<char>(static_cast<char>(method), container);
            WriteData<std::string>(objective_name, container);
            if (method != SetScoreMethod::Remove)
            {
                WriteData<VarInt>(score, container);
            }
#else
            WriteData<std::string>(objective_name, container);
            WriteData<VarInt>(score, container);
            WriteOptional<Chat>(display, container);
            WriteOptional<NumberFormat>(number_format, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["owner"] = owner;
            output["objective_name"] = objective_name;
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
            output["method"] = method;
            if (method != SetScoreMethod::Remove)
            {
                output["score"] = score;
            }
#else
            output["score"] = score;
            if (display.has_value())
            {
                output["display"] = display.value();
            }
            if (number_format.has_value())
            {
                output["number_format"] = number_format.value();
            }
#endif

            return output;
        }

    private:
        std::string owner;
        std::string objective_name;
        int score = 0;
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        SetScoreMethod method;
#else
        std::optional<Chat> display;
        std::optional<NumberFormat> number_format;
#endif

    };
} //ProtocolCraft
