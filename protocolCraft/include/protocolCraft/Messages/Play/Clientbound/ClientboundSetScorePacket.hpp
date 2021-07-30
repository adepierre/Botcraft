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
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x45;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x48;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x4C;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x4D;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x4D;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x4D;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x56;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Score";
        }

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

        const int GetScore() const
        {
            return score;
        }

        const SetScoreMethod GetMethod() const
        {
            return method;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            owner = ReadData<std::string>(iter, length);
            method = (SetScoreMethod)ReadData<char>(iter, length);
            objective_name = ReadData<std::string>(iter, length);
            if (method != SetScoreMethod::Remove)
            {
                score = ReadVarInt(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(owner, container);
            WriteData<char>((char)method, container);
            WriteData<std::string>(objective_name, container);
            if (method != SetScoreMethod::Remove)
            {
                WriteVarInt(score, container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value val(picojson::object_type, false);
            picojson::object& object = val.get<picojson::object>();

            object["owner"] = picojson::value(owner);
            object["method"] = picojson::value((double)method);
            object["objective_name"] = picojson::value(objective_name);
            if (method != SetScoreMethod::Remove)
            {
                object["score"] = picojson::value((double)score);
            }

            return val;
        }

    private:
        std::string owner;
        std::string objective_name;
        int score;
        SetScoreMethod method;

    };
} //ProtocolCraft