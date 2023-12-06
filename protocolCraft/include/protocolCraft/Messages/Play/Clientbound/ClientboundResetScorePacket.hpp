#pragma once

#if PROTOCOL_VERSION > 764 /* > 1.20.3 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundResetScorePacket : public BaseMessage<ClientboundResetScorePacket>
    {
    public:
#if   PROTOCOL_VERSION == 765 /* 1.20.3 */
        static constexpr int packet_id = 0x42;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Reset Score";

        virtual ~ClientboundResetScorePacket() override
        {

        }

        void SetOwner(const std::string& owner_)
        {
            owner = owner_;
        }

        void GetObjectiveName(const std::optional<std::string>& objective_name_)
        {
            objective_name = objective_name_;
        }


        const std::string& GetOwner() const
        {
            return owner;
        }

        const std::optional<std::string>& GetObjectiveName() const
        {
            return objective_name;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            owner = ReadData<std::string>(iter, length);
            objective_name = ReadOptional<std::string>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(owner, container);
            WriteOptional<std::string>(objective_name, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["owner"] = owner;
            if (objective_name.has_value())
            {
                output["objective_name"] = objective_name.value();
            }

            return output;
        }

    private:
        std::string owner;
        std::optional<std::string> objective_name;

    };
} //ProtocolCraft
#endif
