#pragma once

#include "protocolCraft/BaseMessage.hpp"

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
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x45;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x48;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x4C;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578 || PROTOCOL_VERSION == 735 ||  \
      PROTOCOL_VERSION == 736 || PROTOCOL_VERSION == 751 ||  \
      PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x4D;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 ||  \
      PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x56;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x59;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x57;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x5B;
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

        void SetMethod(const SetScoreMethod method_)
        {
            method = method_;
        }


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

        SetScoreMethod GetMethod() const
        {
            return method;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            owner = ReadData<std::string>(iter, length);
            method = static_cast<SetScoreMethod>(ReadData<char>(iter, length));
            objective_name = ReadData<std::string>(iter, length);
            if (method != SetScoreMethod::Remove)
            {
                score = ReadData<VarInt>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(owner, container);
            WriteData<char>(static_cast<char>(method), container);
            WriteData<std::string>(objective_name, container);
            if (method != SetScoreMethod::Remove)
            {
                WriteData<VarInt>(score, container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["owner"] = owner;
            output["method"] = method;
            output["objective_name"] = objective_name;
            if (method != SetScoreMethod::Remove)
            {
                output["score"] = score;
            }

            return output;
        }

    private:
        std::string owner;
        std::string objective_name;
        int score = 0;
        SetScoreMethod method;

    };
} //ProtocolCraft
